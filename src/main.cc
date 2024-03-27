#include "brightness.h"
#include <iostream>

int main (int argc, char *argv[]) {
    int brightness;
    if (argc == 1)
        brightness = 100;
    else
        brightness = atoi(argv[1]);
    std::cout << brightness << std::endl;
    BOOL result = set_brightness(brightness);
    return result ? 0 : 1;
}
