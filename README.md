# Desktop Darkener
simple command line tool to make windows darker

# Usage
Compile this with cl.exe and just run.
You can give the brightness as a single command line argument 0-100 value. For example, when you want to reduce the brightness by half, run
```
./main.exe 50
```

# Why Desktop Darkener
There are many software that can reduce the monitor brightness pushing device limits, but there are several problems with them.
## Standard Night Light Settings
Users do not need to any installation processes to access the "night light" settings, but it doesn't provide you with that much darkness. In addition, intensely yellowish monitors looks so weird.
## Other Free software / shareware
There are many software that claims that can reduce monitor brightness. However, most of them just overlay a "gray sheet" on screen, so they cannot darken some elements such as context menu. 

Destop Darkener solves those problems. This software use ```SetDeviceGammaRamp``` function in Win32 API. This function will efficiently darken you screen. Now, you don't need to go eye clinic that often!

# Limitation
As stated [here](https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setdevicegammaramp), the behavior of ```SetDeviceGammaRamp``` is unstable. This software may not work on all environments.
