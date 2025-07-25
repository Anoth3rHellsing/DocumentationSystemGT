@echo off
REM Build and run DocumentationSystemGT on Windows
REM Installs dependencies via Chocolatey and builds using CMake

where choco >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
  echo Chocolatey is required but was not found.
  echo Install it from https://chocolatey.org/ and re-run this script.
  pause
  exit /b 1
)

choco install -y visualstudio2022buildtools cmake git sqlite
if %ERRORLEVEL% NEQ 0 (
  echo Failed to install dependencies.
  pause
  exit /b 1
)

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022"
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
