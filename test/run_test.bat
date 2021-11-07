echo off
premake5 gmake2
if %ERRORLEVEL% == 0 (
    cd ./build
    make config=test
    if %ERRORLEVEL% == 0 (
        cd ./bin/Test/
        data_structure.exe
    )
) else (
    echo failed to build 
)
