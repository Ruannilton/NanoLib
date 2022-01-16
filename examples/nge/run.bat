echo off
premake5 gmake2
if %ERRORLEVEL% == 0 (
    cd ./build
    make
    if %ERRORLEVEL% == 0 (
        cd ./bin/Debug/
        data_structure.exe
    )
) else (
    echo failed to build 
)
