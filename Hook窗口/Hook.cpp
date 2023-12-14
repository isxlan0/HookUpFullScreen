#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_GETMINMAXINFO: {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMaxTrackSize.x = lpMMI->ptMinTrackSize.x;
        lpMMI->ptMaxTrackSize.y = lpMMI->ptMinTrackSize.y;
        lpMMI->ptMaxSize.x = lpMMI->ptMinTrackSize.x;
        lpMMI->ptMaxSize.y = lpMMI->ptMinTrackSize.y;
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
     std::cout << R"(
 _   _             _      ____         __  ___             _                
| | | | ___   ___ | | __ | __ ) _   _  \ \/ (_) __ _  ___ | |    __ _ _ __  
| |_| |/ _ \ / _ \| |/ / |  _ \| | | |  \  /| |/ _` |/ _ \| |   / _` | '_ \ 
|  _  | (_) | (_) |   <  | |_) | |_| |  /  \| | (_| | (_) | |__| (_| | | | |
|_| |_|\___/ \___/|_|\_\ |____/ \__, | /_/\_\_|\__,_|\___/|_____\__,_|_| |_|
                                |___/                                       
    )" << std::endl;

    std::cout << "程序作者XiaoLan(Alpha)" << std::endl;
    std::cout << "Program author XiaoLan(Alpha)" << std::endl;
    std::cout << "Github开源地址：https://github.com/isxlan0/HookUpFullScreen" << std::endl;
    std::cout << "Github open source address: https://github.com/isxlan0/HookUpFullScreen" << std::endl;

    std::cout << "Hello, World!" << std::endl;

    HWND hwnd = FindWindow(L"UnityWndClass", L"原神");

    if (hwnd == nullptr) {
        std::cerr << "找不到游戏窗口！" << std::endl;
        return 1;
    }

    LONG_PTR g_originalStyle = GetWindowLongPtr(hwnd, GWL_STYLE);

    SetWindowLongPtr(hwnd, GWL_STYLE, g_originalStyle & ~WS_OVERLAPPEDWINDOW);

    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

    ShowWindow(hwnd, SW_MAXIMIZE);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(5000);

    return 0;
}
