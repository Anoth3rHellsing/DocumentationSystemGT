@echo off
REM Build and run DocumentationSystemGT on Windows
cd /d "%~dp0"

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

REM Acquire dependencies using vcpkg
set "VCPKG_ROOT=%cd%\vcpkg"
if not exist "%VCPKG_ROOT%" (
  git clone https://github.com/microsoft/vcpkg "%VCPKG_ROOT%"
  call "%VCPKG_ROOT%\bootstrap-vcpkg.bat"
)
"%VCPKG_ROOT%\vcpkg.exe" install sqlite3 qt5-base qt5-tools
if %ERRORLEVEL% NEQ 0 (
  echo vcpkg failed to install packages.
  pause
  exit /b 1
)

refreshenv
if %ERRORLEVEL% NEQ 0 (
  echo Failed to refresh environment.
  pause
  exit /b 1
)

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake"
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
Release\doc_gui.exe
pause
