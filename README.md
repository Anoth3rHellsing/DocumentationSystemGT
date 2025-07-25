# DocumentationSystemGT

Documentation System for CRM case documentation.

This repository provides a minimal C++ project demonstrating how to
store raw technical support case information. `CaseData` keeps details
such as the caller, scanner information and mission‑critical checklist
results. Case records are stored in a local SQLite database.

Helper methods produce formatted strings used in CRM notes:
- `buildTitle()` → `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`
- `buildPhonecallTitle()` → `PHONECALLYYYYMMDD`
- `buildInternalNoteTitle()` → `INT-YYYYMMDD`

`CaseData` tracks whether logs were taken, screenshots captured and a
recap email sent. The `buildMissionCriticalChecklist()` helper lists
these items as `TRUE` or `FALSE`.

## Installation (Quick Start)

### Linux (Ubuntu/Debian)

1. **Install dependencies**

   ```bash
   sudo apt-get update
   sudo apt-get install -y build-essential cmake libsqlite3-dev git
   ```

2. **Clone and build**

   ```bash
   git clone <repository-url>
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

4. **Run the example**

   ```bash
   ./doc_sys
   ```

   A `cases.db` file will be created in the working directory.

### Windows

The `build_windows.bat` script automates setup using
[Chocolatey](https://chocolatey.org/) and [vcpkg](https://github.com/microsoft/vcpkg).

Run it from an elevated **Developer Command Prompt for VS** to install
dependencies, build the project, run the tests and launch the example
program. The script locates your Visual Studio installation using
`vswhere.exe` and configures the environment automatically.

If you prefer manual steps:

1. **Install dependencies**

   Install Visual Studio Build Tools (with C++ support), CMake, Git and a
   SQLite3 development package. One approach is to use vcpkg:

   ```powershell
   choco install -y visualstudio2022buildtools cmake git
   git clone https://github.com/microsoft/vcpkg
   .\vcpkg\bootstrap-vcpkg.bat
   .\vcpkg\vcpkg.exe install sqlite3:x64-windows
   ```

2. **Clone and build**

   ```powershell
   git clone <repository-url>
   cd DocumentationSystemGT
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake
   cmake --build . --config Release
   ```

   If you installed SQLite3 manually, omit the toolchain file and pass the
   `-DSQLite3_INCLUDE_DIR` and `-DSQLite3_LIBRARY` options instead.

   ```powershell
   cmake .. -G "Visual Studio 17 2022" -A x64 -DSQLite3_INCLUDE_DIR=C:\path\to\include -DSQLite3_LIBRARY=C:\path\to\sqlite3.lib
   ```

3. **Run the tests (optional)**

   ```powershell
   ctest -C Release --output-on-failure
   ```

4. **Run the example**

   ```powershell
   .\Release\doc_sys.exe
   ```

   The program creates `cases.db` in the current directory and prints
   sample output.

## Recommendations

- Use `-DCMAKE_BUILD_TYPE=Release` to enable optimizations.
- Run the unit tests after making changes to verify your setup.
- Update `build_windows.bat` when new Visual Studio versions are
  released.
- Store the SQLite database on a fast drive if you expect many cases.
- Extend `CaseData` or the example program to integrate with your actual
  CRM workflow.

See the [CHANGELOG](CHANGELOG.md) for release information.
