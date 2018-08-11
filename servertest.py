import socket
import sys
import time
import random

def choose():
    n = random.randint(0, 10)
    if n < 2:
        return 0
    return 1

def send_map(conn):
    conn.sendall("WELCOME\n")
    time.sleep(1)
    conn.sendall("msz 4 4\n")
    for i in range(4):
        for j in range(4):
            msg = "bct "
            msg += str(i) + " " + str(j) + " " + str(choose()) + "\n"
            conn.sendall(msg)

    conn.sendall("ppo 0 0\n")
    conn.sendall("des 3 3\n")
    conn.sendall("done\n")
    time.sleep(1)
    conn.sendall("pnw 1 1\n")
    conn.sendall("pnw 0 0\n")
    conn.sendall("done\n")
    time.sleep(1)
    conn.sendall("start\n")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_addr = ('localhost', 1337)

print >> sys.stderr, 'starting up on %s port %s' % server_addr

sock.bind(server_addr)

sock.listen(2)

while True:
    print >> sys.stderr, 'waiting for connection'
    connection , client_addr = sock.accept()

    try:
        print >>sys.stderr, 'connection from', client_addr

        while True:
            data = connection.recv(2000)
            print >>sys.stderr, 'received [%s]' % data

            if (data and data.strip() == "car"):
                print >> sys.stderr, 'sending data back to client'
                send_map(connection)
            else:
                print >> sys.stderr, 'no more data from ', client_addr
                break
    finally:
        connection.close()


