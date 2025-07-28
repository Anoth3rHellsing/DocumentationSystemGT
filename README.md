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
   sudo apt-get install -y build-essential cmake libsqlite3-dev git
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

4. **Run the example**

   ```bash
   ./doc_sys
   ```

   A `cases.db` file will be created in the working directory.

### Windows

The `build_windows.bat` script automates setup using

[Chocolatey](https://chocolatey.org/). Run it from an elevated **Developer
Command Prompt for VS 2022** to install dependencies, refresh your
environment, build the project, run the tests and launch the example
program.

If you prefer manual steps, open an elevated **Developer Command Prompt**
and switch to a convenient working directory such as `C:\`:

0. **Set your working directory**

   ```powershell
   cd C:\
   ```

1. **Install dependencies**

   Install Visual Studio Build Tools (with C++ support), CMake, Git and
   SQLite. The easiest approach is via Chocolatey:

   ```powershell
   choco install -y visualstudio2022buildtools cmake git sqlite
   refreshenv    # or restart the command prompt
   ```

2. **Clone and build**

   ```powershell
   cd C:\
   git clone https://github.com/Anoth3rHellsing/DocumentationSystemGT
   cd DocumentationSystemGT
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64
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
