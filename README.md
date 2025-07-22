# DocumentationSystemGT

Documentation System for CRM case documentation.

This repository contains a basic C++ project that defines a `CaseData` structure used to store raw information for technical support cases. Cases can be stored in a small SQLite database and a helper method builds the case title in the format `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`.

`CaseData` also provides helpers to build a phone call title (`PHONECALLYYYYMMDD` for the current date) and a phone call note listing basic caller and connection information.

Internal notes use a similar helper for the title (`INT-YYYYMMDD`) and the `buildInternalNote` method which returns one of three variations:

- `Helpjuice Used:\t<Helpjuice/Jira link>`
- `Logs:\tLogs attached (Zip Folder must be attached)`
- `Could not attach logs: <reason>`

`CaseData` tracks three mission critical steps (logs taken, screenshots taken, recap email sent). The `buildMissionCriticalChecklist` helper returns a string listing each item as `TRUE` or `FALSE` so agents can confirm completion.

## Installation (Dumbproof Guide)

1. **Install dependencies**

   On Ubuntu/Debian run:

   ```bash
   sudo apt-get update
   sudo apt-get install -y build-essential cmake libsqlite3-dev
   ```

   Make sure `git` is available so you can clone the repository.

2. **Clone this repository and build the project**

   ```bash
   git clone <repository-url>
   cd DocumentationSystemGT
   mkdir build && cd build
   cmake ..
   make
   ```

3. **(Optional) Run the unit test**

   ```bash
   ctest --output-on-failure
   ```

4. **Run the example application**

   ```bash
   ./doc_sys
   ```

   The program will create a `cases.db` SQLite file in the current directory and
   print some example output.
### Windows

1. **Install dependencies**

   Install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) with C++ support and [CMake](https://cmake.org/download/). The easiest way is via [Chocolatey](https://chocolatey.org/):

   ```powershell
   choco install -y visualstudio2022buildtools cmake git sqlite
   ```

2. **Clone this repository and build the project**

   Open a Developer Command Prompt and run:

   ```powershell
   git clone <repository-url>
   cd DocumentationSystemGT
   mkdir build && cd build
   cmake .. -G "Visual Studio 17 2022"
   cmake --build . --config Release
   ```

3. **(Optional) Run the unit tests**

   ```powershell
   ctest -C Release --output-on-failure
   ```

4. **Run the example application**

   ```powershell
   .\Release\doc_sys.exe
   ```

   The program will create a `cases.db` SQLite file in the current directory and print some example output.

=======
