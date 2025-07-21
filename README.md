# DocumentationSystemGT

Documentation System for CRM case documentation.

This repository contains a basic C++ project that defines a `CaseData` structure used to store raw information for technical support cases. Cases can be stored in a small SQLite database and a helper method builds the case title in the format `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`.

`CaseData` also provides helpers to build a phone call title (`PHONECALLYYYYMMDD` for the current date) and a phone call note listing basic caller and connection information.

Internal notes use a similar helper for the title (`INT-YYYYMMDD`) and the `buildInternalNote` method which returns one of three variations:

- `Helpjuice Used:\t<Helpjuice/Jira link>`
- `Logs:\tLogs attached (Zip Folder must be attached)`
- `Could not attach logs: <reason>`


kqtui1-codex/implement-case-documentation-storage-in-c++
`CaseData` tracks three mission critical steps (logs taken, screenshots taken, recap email sent). The `buildMissionCriticalChecklist` helper returns a string listing each item as `TRUE` or `FALSE` so agents can confirm completion.

Build the project with CMake:

```bash
mkdir build && cd build
cmake ..
make
./doc_sys
```
