import sqlite3
import msgpack
import socket
import os
from hashlib import sha256

import prctl
from Crypto.Cipher import ChaCha20


class Db:
    def __init__(self, dbpath: str):
        self.dbpath = dbpath
        self.dbconn = None
        self.dbcurs = None

    def __enter__(self):
        self.dbconn = sqlite3.connect(self.dbpath)
        self.dbcurs = self.dbconn.cursor()
        self.dbcurs.execute('CREATE TABLE IF NOT EXISTS messages '
                            '(sender text, '
                            'receiver text, '
                            'message text )'
                            )
        self.dbconn.commit()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.dbcurs.close()
        self.dbconn.close()

    def insert_message(self, sender, receiver, message):
        self.dbcurs.execute('INSERT INTO main.messages VALUES(?, ?, ?)', (sender, receiver, message))
        self.dbconn.commit()

    def get_all_messages(self, person1, person2):
        text = ''
        self.dbcurs.execute('SELECT * FROM main.messages WHERE (sender=? OR sender=?) AND (receiver=? OR receiver=?)',
                       (person1, person2, person2, person1))
        for m in self.dbcurs.fetchall():
            text += '{}->{}: {}\n'.format(*m)
        return text


def make_dhe_key_from_ask(sock, a):
    data = sock.recv(1024)
    client_p, client_g = msgpack.unpackb(data)
    client_p, client_g = int.from_bytes(client_p, byteorder='little'), int.from_bytes(client_g, byteorder='little')
    B = (client_g ** a) % client_p
    sock.send(B.to_bytes(100, byteorder='little'))
    A = int.from_bytes(sock.recv(1024), byteorder='little')
    dhe_key = (A ** a) % client_p
    sock.send('OK'.encode('utf8'))
    return dhe_key


def ask_and_make_dhe_key(sock, p, g, a):
    sock.send(msgpack.packb([p.to_bytes(100, byteorder='little'), g.to_bytes(100, byteorder='little')]))
    A = (g ** a) % p
    B = int.from_bytes(sock.recv(1024), byteorder='little')
    sock.send(A.to_bytes(100, byteorder='little'))
    dhe_key = (B ** a) % p
    ok = sock.recv(1024)
    if ok.decode('utf8') != 'OK':
        return None
    return dhe_key


def resolve_challenge(sock, hashed_passwd_salt: str):
    chall = sock.recv(1024)
    sock.sendall(sha256(chall + hashed_passwd_salt.encode('utf8')).hexdigest().encode('utf8'))


def propose_challenge(sock, client_hash: str) -> bool:
    if not client_hash:
        # If the server is not known
        return False
    chall = os.urandom(64)
    sock.sendall(chall)
    chall_response = sock.recv(1024)
    if sha256(chall + client_hash.encode('utf8')).hexdigest() == chall_response.decode('utf8'):
        return True
    return False


def send_message(sock, key, db: Db, client_name, server_name):
    message = input('>>>')
    cipher = ChaCha20.new(key=key)
    c_message = cipher.encrypt(message.encode('utf8'))
    sock.send(msgpack.packb([c_message, cipher.nonce]))
    db.insert_message(client_name, server_name, message)


def receive_message(sock, key, db: Db, client_name, server_name):
    c_message, nonce = msgpack.unpackb(sock.recv(2048))
    decipher = ChaCha20.new(key=key, nonce=nonce)
    message = decipher.decrypt(c_message).decode('utf8')
    print(message)
    db.insert_message(server_name, client_name, message)


def drop_root_privileges():
    if os.getuid():
        # We are not root
        return
    os.setgid(1000)
    os.setuid(1000)


def drop_capabilities():
    if os.getuid():
        return
    prctl.set_no_new_privs(True)
    prctl.capbset.drop(prctl.capbset.net_admin)
    prctl.capbset.drop(prctl.capbset.net_bind_service)
