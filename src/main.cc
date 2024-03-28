#include "brightness.h"
#include <iostream>

std::wstring exe_dir() {
    WCHAR buffer[MAX_PATH];
    GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    std::wstring full_path(buffer);
    std::wstring::size_type pos = full_path.find_last_of(L"\\/");
    if (pos != std::string::npos) {
        return full_path.substr(0, pos);
    }
    throw std::runtime_error("invalid path");
}

int WINAPI WinMain(HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, 
    int nCmdShow
    ) {
    std::wstring path = exe_dir() + L"/brightness.txt";
    int brightness;
    if (__argc == 1)
        brightness = 100;
    else if (strcmp(__argv[1], "toggle") == 0) {
        int current = get_current_brightness(path);
        if (current > 50)
            brightness = 0;
        else
            brightness = 100;
    }
    else
        brightness = atoi(__argv[1]);
    
    std::cout << brightness << std::endl;
    BOOL result = set_brightness(brightness, path);
    return result ? 0 : 1;
}
