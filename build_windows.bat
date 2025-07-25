@echo off
REM Move to the directory containing this script
cd /d "%~dp0"
REM Build and run DocumentationSystemGT on Windows
REM Installs dependencies via Chocolatey and builds using CMake

where choco >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
  echo Chocolatey is required but was not found.
  echo Install it from https://chocolatey.org/ and re-run this script.
  pause
  exit /b 1
)

choco install -y visualstudio2022buildtools cmake git
if %ERRORLEVEL% NEQ 0 (
  echo Failed to install dependencies.
  pause
  exit /b 1
)

REM Locate the latest Visual Studio instance and load its environment
for /f "usebackq tokens=*" %%i in ( `"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath` ) do set VS_PATH=%%i
if not defined VS_PATH (
  echo Could not locate a valid Visual Studio instance.
  pause
  exit /b 1
)
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

REM Acquire SQLite3 using vcpkg
if not exist vcpkg (
  git clone https://github.com/microsoft/vcpkg
  if %ERRORLEVEL% NEQ 0 (
    echo Failed to clone vcpkg.
    pause
    exit /b 1
  )
  call vcpkg\bootstrap-vcpkg.bat
  if %ERRORLEVEL% NEQ 0 (
    echo vcpkg bootstrap failed.
    pause
    exit /b 1
  )
)

vcpkg\vcpkg.exe install sqlite3:x64-windows
if %ERRORLEVEL% NEQ 0 (
  echo Failed to install sqlite3 with vcpkg.
  pause
  exit /b 1
)

REM Locate the latest Visual Studio instance and load its environment
for /f "usebackq tokens=*" %%i in ( `"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath` ) do set VS_PATH=%%i
if not defined VS_PATH (
  echo Could not locate a valid Visual Studio instance.
  pause
  exit /b 1
)
call "%VS_PATH%\VC\Auxiliary\Build\vcvars64.bat"

REM Acquire SQLite3 using vcpkg
if not exist vcpkg (
  git clone https://github.com/microsoft/vcpkg
  if %ERRORLEVEL% NEQ 0 (
    echo Failed to clone vcpkg.
    pause
    exit /b 1
  )
  call vcpkg\bootstrap-vcpkg.bat
  if %ERRORLEVEL% NEQ 0 (
    echo vcpkg bootstrap failed.
    pause
    exit /b 1
  )
)

vcpkg\vcpkg.exe install sqlite3:x64-windows

if %ERRORLEVEL% NEQ 0 (
  echo Failed to install sqlite3 with vcpkg.
  pause
  exit /b 1
)

set VCPKG_TOOLCHAIN_FILE=%CD%\vcpkg\scripts\buildsystems\vcpkg.cmake

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN_FILE%

if %ERRORLEVEL% NEQ 0 (
  echo cmake configuration failed.
  pause
  exit /b 1
)

cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
  echo Build failed.
  pause
  exit /b 1
)

ctest -C Release --output-on-failure

Release\doc_sys.exe
pause
