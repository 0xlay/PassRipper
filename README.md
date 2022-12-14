# PassRipper
The PassRipper is a simple program for cracking password to file.</br> 
### DISCLAIMER!!! You can use this program only for cracking your personal files!

# Build in Windows
### Dependencies for build
* Visual Studio 2019 and high
* CMake 3.20 and high
* OpenSSL 1.0.2 and high
* JSON (Nlohmann) 3.11.2 and high
* GoogleTest (optional)

### Clone repository (with submodules)
```git clone --recursive https://github.com/0xlay/PassRipper.git```

### Install the OpenSSL lib
1. Run the Visual Studio Developer Command Prompt for target platform (x86 or x64) </br>
```C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019\Visual Studio Tools\VC```
2. Go to the ```ThirdParty/OpenSSL/``` folder
3. Build
   - For x64 </br>
   ```perl Configure VC-WIN64A no-asm --prefix=Full-Path/ThirdParty/OpenSSL/build/x64/Release/``` </br>
   ```ms\do_win64a``` </br>
   ```nmake -f ms\nt.mak``` </br>
   ```nmake -f ms\nt.mak install```
   - For x86 </br>
     ```perl Configure VC-WIN32 no-asm --prefix=Full-Path/ThirdParty/OpenSSL/build/x86/Release/``` </br>
     ```ms\do_ms``` </br>
     ```nmake -f ms\nt.mak``` </br>
     ```nmake -f ms\nt.mak install```

# How to use
```PassRipper.exe X:\\PathToEncryptionFile --alphabet=all --password-length=4 --threads=4``` </br>
or </br>
```PassRipper.exe X:\\PathToEncryptionFile `X:\\PathToConfig.json```