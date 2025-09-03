///add vfw32 in codeblocks linkers settings

#include <windows.h>
#include <vfw.h>
#include <iostream>

#pragma comment(lib, "vfw32.lib")

int main() {
    // Initialize AVI library
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

    std::cout << "[+] Recording screen... Press ESC to stop.\n";

    while (true) {
        // Check for ESC key
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            std::cout << "[*] ESC pressed. Stopping recording...\n";
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
    return 0;
}
