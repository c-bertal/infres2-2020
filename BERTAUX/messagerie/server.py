import socket
import random
from hashlib import sha256
import common


dbfile = 'server.sqlite3'
server_name = 'Yopserver'

port = 12080

server_salt = b'\x15\x94\xb8\xed#\xe6!ae\xdd\xbbZ\xa4h!Y\xcfg\xee\xca9\x02`%.\xda#\x07cO#\xbe'
password = 'root'  # input()

hashed_passwd_salt = sha256(server_salt + password.encode('utf8')).hexdigest()

known_hashes = {
    'Yopclient': 'bca231ba0562dc7bfb01e1068ff7451aea8049d03f93a5ce3a3abcb94dc9292d'
}

# Diffie Hellman
diffie_hellman = {
    'a': random.randint(1, 1000)
}

# Socket creation
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)



# capabilities
common.drop_capabilities()

# drop root
common.drop_root_privileges()


try:
    sock.bind(('', port))
    sock.listen(3)

    while True:
        conn, addr = sock.accept()
        with conn:
            print(f'Client connected : {addr}')

            # Diffie Hellman
            dhe_key = common.make_dhe_key_from_ask(conn, **diffie_hellman)

            # Symmetric key used for ChaCha20 encryption
            sym_key = sha256(dhe_key.to_bytes(100, byteorder='little')).digest()

            # get client name
            client_name = conn.recv(1024).decode('utf8')
            print(f'Communicating with {client_name}')

            # Client auth
            if not common.propose_challenge(conn, known_hashes.get(client_name)):
                raise ValueError('Client failed to authenticate')
            print('Client authenticated')

            # Self auth
            conn.sendall(server_name.encode('utf8'))
            common.resolve_challenge(conn, hashed_passwd_salt)

            with common.Db(dbfile) as db:
                old_messages = db.get_all_messages(server_name, client_name)
                if old_messages is None:
                    print('No old messages')
                else:
                    print(old_messages)

                # chat loop
                while True:
                    common.receive_message(conn, sym_key, db, client_name, server_name)
                    common.send_message(conn, sym_key, db, client_name, server_name)


except Exception as e:
    raise
finally:
    sock.close()
