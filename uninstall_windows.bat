@echo off
REM Clean uninstall of DocumentationSystemGT and its dependencies
cd /d "%~dp0"

where choco >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
  echo Chocolatey is required but was not found.
  echo Install it from https://chocolatey.org/ and re-run this script.
  pause
  exit /b 1
)

echo Uninstalling packages installed with Chocolatey...
choco uninstall -y visualstudio2022buildtools cmake git

REM Remove vcpkg packages and directory if present
if exist vcpkg (
  vcpkg\vcpkg.exe remove sqlite3:x64-windows qt5-base:x64-windows qt5-tools:x64-windows
  rmdir /s /q vcpkg
)

REM Remove build artifacts and database files
if exist build rmdir /s /q build
if exist cases.db del /q cases.db
if exist test.db del /q test.db

REM Optionally remove Release folder if left over
if exist Release rmdir /s /q Release

echo Uninstallation complete.
pause
