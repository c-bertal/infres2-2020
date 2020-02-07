import random
import socket
from hashlib import sha256
from Crypto.Util import number
import common
import prctl

# Database
dbfile = 'client.sqlite3'
client_name = 'Yopclient'

# Used for authentication
client_salt = b'\x95G\xd9\xd4\x11e\xdbq\xe8\tH\t\xb3SE\x99\x933\xa6h\xe7)\x97\x08(e\xa3h$\xa6\xbd\xb7'  # 32 octets
password = 'test'  # ou via input()
hashed_passwd_salt = sha256(client_salt + password.encode('utf8')).hexdigest()
# = 'bca231ba0562dc7bfb01e1068ff7451aea8049d03f93a5ce3a3abcb94dc9292d'

known_hashes = {
    'Yopserver': 'af7e8bb0a48bf99a8f46974e821fe07c877db728ca4605a9c1c34be5cd32d292'
}

diffie_hellman = {
    'p': number.getPrime(512),
    'g': random.randint(1, 1000),
    'a': random.randint(1, 1000)
}

# Server information
server = '127.0.0.1'
port = 12080

# Socket creation
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)


# capabilities
common.drop_capabilities()

# drop root
common.drop_root_privileges()

try:
    sock.connect((server, port))

    # Diffie hellman
    dhe_key = common.ask_and_make_dhe_key(sock, **diffie_hellman)
    if dhe_key is None:
        raise ValueError('Unable to create DHE key')

    # Symmetric key used for ChaCha20 encryption
    sym_key = sha256(dhe_key.to_bytes(100, byteorder='little')).digest()

    # send our name
    sock.sendall(client_name.encode('utf8'))

    # self authentication
    common.resolve_challenge(sock, hashed_passwd_salt)

    # Get server name
    server_name = sock.recv(1024).decode('utf8')
    print(f'Connected with {server_name}')

    # server authentication
    if not common.propose_challenge(sock, known_hashes.get(server_name)):
        raise ValueError('Server failed to authenticate')
    print('Server authenticated')

    with common.Db(dbfile) as db:
        old_messages = db.get_all_messages(client_name, server_name)
        if old_messages is None:
            print('No old messages')
        else:
            print(old_messages)

        # Loop chat
        while True:
            common.send_message(sock, sym_key, db, client_name, server_name)
            common.receive_message(sock, sym_key, db, client_name, server_name)

except Exception as e:
    raise
finally:
    sock.close()
