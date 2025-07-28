# DocumentationSystemGT

A minimal C++ example that stores CRM case data in a local SQLite database. The `CaseData` structure records caller and scanner details along with a mission‑critical checklist.

Helper functions format CRM notes:
- `buildTitle()` → `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`
- `buildPhonecallTitle()` → `PHONECALLYYYYMMDD`
- `buildPhonecallNote()` → caller and connection info
- `buildInternalNoteTitle()` → `INT-YYYYMMDD`
- `buildInternalNote()` → "Helpjuice Used:\t<link>" or "Logs:\tLogs attached" or "Could not attach logs: <reason>"

`CaseData` also tracks whether logs, screenshots and a recap email were sent. `buildMissionCriticalChecklist()` lists these as `TRUE` or `FALSE`:

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
   C:\vcpkg\vcpkg.exe install sqlite3
   refreshenv    # or restart the command prompt
   ```

2. **Clone and build**

   ```powershell
   git clone https://github.com/Anoth3rHellsing/DocumentationSystemGT
   cd DocumentationSystemGT
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
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

   The program creates `cases.db` in the current directory and prints sample output.

## Recommendations

- Use `-DCMAKE_BUILD_TYPE=Release` to enable optimizations.
- Manage libraries with [vcpkg](https://github.com/microsoft/vcpkg) on Windows.
- Run the unit tests after making changes to verify your setup.
- Update `build_windows.bat` when new Visual Studio versions are released.
- Store the SQLite database on a fast drive if you expect many cases.
- Extend `CaseData` or the example program to integrate with your actual CRM workflow.

See the [CHANGELOG](CHANGELOG.md) for release information.
