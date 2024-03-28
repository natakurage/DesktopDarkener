#include "brightness.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, 
    HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, 
    int nCmdShow
    ) {
    int brightness;
    if (argc == 1)
        brightness = 100;
    else
        brightness = atoi(argv[1]);
    std::cout << brightness << std::endl;
    BOOL result = set_brightness(brightness);
    return result ? 0 : 1;
}
