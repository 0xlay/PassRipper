# PassRipper
App for password brute force

# Build
### Dependencies for build
* Visual Studio 2019 and high
* CMake 3.20 and high
* OpenSSL 1.0.2 and high

### Install the OpenSSL lib
1. Run the Visual Studio Developer Command Prompt </br>
```C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019\Visual Studio Tools\VC```
2. Go to the ```ThirdParty/OpenSSL/``` folder
3. Build
   - For x64 </br>
   ```perl Configure VC-WIN64A no-asm --prefix=../../buid/OpenSSL/x64/Release/``` </br>
   ```ms\do_ms``` </br>
   ```nmake -f ms\nt.mak``` </br>
   ```nmake -f ms\nt.mak install```
   - For x86 </br>
     ```perl Configure VC-WIN32 no-asm --prefix=../../buid/OpenSSL/x86/Release/``` </br>
     ```ms\do_ms``` </br>
     ```nmake -f ms\nt.mak``` </br>
     ```nmake -f ms\nt.mak install```
