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
[Chocolatey](https://chocolatey.org/). Run it from an elevated Developer
Command Prompt to install dependencies, build the project, run the tests
and launch the example program.

If you prefer manual steps:

1. **Install dependencies**

   Install Visual Studio Build Tools (with C++ support), CMake, Git and
   SQLite. The easiest approach is via Chocolatey:

   ```powershell
   choco install -y visualstudio2022buildtools cmake git sqlite
   ```

2. **Clone and build**

   ```powershell
   git clone <repository-url>
   cd DocumentationSystemGT
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022"
   cmake --build . --config Release
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
