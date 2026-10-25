@echo off
setlocal enabledelayedexpansion

echo [Generate with Python...]
python -X pycache_prefix="%~dp0.cache" gen_bench.py


echo [Detecting Visual Studio via vswhere...]
set "VS_PATH="

for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VS_PATH=%%i"
)

if not defined VS_PATH (
    echo [Error] No Visual Studio environment with C++ components was found.
    pause
    exit /b
)

set "VCVARS_BAT=%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

if not exist "%VCVARS_BAT%" (
    echo [Error] vcvars64.bat was not found at the following path: "%VCVARS_BAT%"
    pause
    exit /b
)

echo [Spawning new console window...]
rem Key /k keeps the new window open after all commands have finished running
start "MSVC Compilation & Benchmark" cmd /k "call "%VCVARS_BAT%" && echo [Compiling with MSVC...] && cl /O2 /Oi /EHsc /std:c++20 /arch:AVX2 /Fe:bench_msvc.exe /bigobj benchmark.cpp && echo [Running Benchmark...] && (if not exist result mkdir result) && bench_msvc.exe & echo [Cleaning up...] & del *.obj"

endlocal