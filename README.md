# DocumentationSystemGT

Documentation system for storing CRM case information.

This repository provides a minimal C++ project that demonstrates how to
store raw technical support case information. The `CaseData` struct keeps
details such as the caller, scanner information and mission‑critical
checklist results. Case records are stored in a local SQLite database.

Helper methods produce formatted strings for CRM notes:
- `buildTitle()` → `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`
- `buildPhonecallTitle()` → `PHONECALLYYYYMMDD`
- `buildPhonecallNote()` → lists caller and connection details
- `buildInternalNoteTitle()` → `INT-YYYYMMDD`
- `buildInternalNote()` → "Helpjuice Used:\t<link>" or "Logs:\tLogs attached" or
  "Could not attach logs: <reason>"

`CaseData` tracks whether logs were taken, screenshots captured and a
recap email sent. The `buildMissionCriticalChecklist()` helper lists
these items as `TRUE` or `FALSE`:

```
Logs Taken?        TRUE
Screenshots taken? FALSE
Recap Email sent?  TRUE
```

## Installation (Quick Start)

### Linux (Ubuntu/Debian)

1. **Install dependencies**

   ```bash
   sudo apt-get update
   sudo apt-get install -y build-essential cmake libsqlite3-dev qtbase5-dev \
       qttools5-dev git
   ```

2. **Clone and build**

   ```bash
   git clone https://github.com/Anoth3rHellsing/DocumentationSystemGT
   cd DocumentationSystemGT
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   cmake --build .
   ```

3. **Run the test suite (optional)**

   ```bash
   ctest --output-on-failure
   ```

4. **Run the examples**

   ```bash
   ./doc_sys      # command-line example
   ./doc_gui      # Qt GUI example
   ```

   A `cases.db` file will appear in the working directory.

### Windows

You can run `build_windows.bat` from an elevated **Developer Command Prompt for VS 2022** to install tools with Chocolatey, refresh the environment and build the project.

If you prefer manual steps, follow this procedure in an elevated Developer Command Prompt.

0. **Set your working directory**

   ```powershell
   cd C:\
   ```

1. **Install prerequisites**

   ```powershell
   choco install -y visualstudio2022buildtools cmake git
   git clone https://github.com/microsoft/vcpkg C:\vcpkg
   C:\vcpkg\bootstrap-vcpkg.bat
   C:\vcpkg\vcpkg.exe install sqlite3 qt5-base qt5-tools
   refreshenv    # or restart the command prompt
   ```

   If you prefer not to use vcpkg, install SQLite3 and Qt 5 manually. Download
   the 64‑bit SQLite3 binaries from <https://www.sqlite.org/download.html> and
   extract them to a folder like `C:\sqlite`. Install Qt using the [Qt Online
   Installer](https://www.qt.io/download) and note the path to the MSVC build,
   for example `C:\Qt\5.15.3\msvc2019_64`.

2. **Clone and build**

   ```powershell
   cd C:\
   git clone https://github.com/Anoth3rHellsing/DocumentationSystemGT
   cd DocumentationSystemGT
   mkdir build
   cd build
   ```

   Using vcpkg:

   ```powershell
   cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
   cmake --build . --config Release
   ```

   For manual installs specify the paths to SQLite3 and Qt:

   ```powershell
   cmake .. -G "Visual Studio 17 2022" -A x64 -DSQLite3_INCLUDE_DIR=C:\sqlite -DSQLite3_LIBRARY=C:\sqlite\sqlite3.lib -DCMAKE_PREFIX_PATH=C:\Qt\5.15.3\msvc2019_64
   cmake --build . --config Release
   ```
                                                  
3. **Run the tests (optional)**

   ```powershell
   ctest -C Release --output-on-failure
   ```

4. **Run the examples**

   ```powershell
   .\Release\doc_sys.exe  # command-line example
   .\Release\doc_gui.exe  # Qt GUI example
   ```

   The program creates `cases.db` in the current directory and prints sample output.

### Clean Uninstall on Windows

Run `uninstall_windows.bat` from an elevated Developer Command Prompt to
remove the Chocolatey packages, delete the `vcpkg` folder, the `build`
directory and any generated database files.
  
## Recommendations

- Use `-DCMAKE_BUILD_TYPE=Release` to enable optimizations.
- Run the unit tests after making changes to verify your setup.
- Update `build_windows.bat` when new Visual Studio versions are
  released.
- Store the SQLite database on a fast drive if you expect many cases.
- Extend `CaseData` or the example program to integrate with your actual
  CRM workflow.

See the [CHANGELOG](CHANGELOG.md) for release information.
