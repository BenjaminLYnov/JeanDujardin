REM Setup the environment for the build process

REM If output directory exists, remove it
if exist output rmdir /s /q output

REM Setup with CMake
cmake -B build

pause