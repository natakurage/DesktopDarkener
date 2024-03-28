#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#include <windows.h>
#include <cmath>
#include <iostream>
#include <fstream>

const int MAX_VALUE = 65535;
const int MIN_VALUE = 32768;
const int MAX_TRIES = 20;

BOOL set_monitor_brightness(HDC hdc, float brightness, float gamma)
{
    if (brightness < 0 && 1 < brightness)
    {
        throw "brightness must be 0 to 1";
    }
    float coef = brightness * (MAX_VALUE - MIN_VALUE) + MIN_VALUE;
    WORD ramp[3][256];
    for (int color = 0; color < 3; color++)
    {
        for (int x = 0; x < 256; x++)
        {
            ramp[color][x] = WORD(coef * x / 256);
        }
    }
    int result = SetDeviceGammaRamp(hdc, ramp);
    return result;
}

BOOL CALLBACK MyMonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    float brightness = float(dwData) / 100;
    float gamma = 1.0;
    BOOL result = set_monitor_brightness(hdcMonitor, brightness, gamma);
    std::cout << (result ? "brightness ok" : "brightness failed") << std::endl;
    return result;
}

BOOL set_brightness(int brightness, std::wstring path)
{
    for (int tries = 0; tries < MAX_TRIES; tries++)
    {
        HDC AllDC = GetDC(NULL);
        bool result = EnumDisplayMonitors(AllDC, NULL, MyMonitorEnumProc, brightness);
        std::cout << (result ? "enum ok" : "enum failed") << std::endl;
        bool result2 = ReleaseDC(0, AllDC);
        std::cout << (result2 ? "released" : "not released") << std::endl;
        if (result) {
            if (!path.empty()) {
                std::ofstream outputfile(path);
                outputfile << brightness;
            } else
                std::clog << "didn't save brightness because path is empty" << std::endl;
            return true;
        } else {
            std::cout << tries + 1 << "th trial failed, retrying..." << std::endl;;
        }
    }
    std::cout << "Failed" << MAX_TRIES << "times, finished" << std::endl;;
    return false;
}

int get_current_brightness(std::wstring path)
{
    if (path.empty()) {
        std::cerr << "path is empty" << std::endl;
        return 0;
    }
    std::ifstream inputfile(path);
    if (!inputfile) {
        std::cerr << "file not found" << std::endl;
        return 0;
    }
    int brightness;
    inputfile >> brightness;
    std::cout << brightness << std::endl;
    return brightness;
}
