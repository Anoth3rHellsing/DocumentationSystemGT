# DocumentationSystemGT

Documentation System for CRM case documentation.

This repository contains a basic C++ project that defines a `CaseData` structure used to store raw information for technical support cases. Cases can be stored in a small SQLite database and a helper method builds the case title in the format `||CompanyName|SIDSubscriptionID|BriefDescriptionTitle|CaseID`.

`CaseData` also provides helpers to build a phone call title (`PHONECALLYYYYMMDD` for the current date) and a phone call note listing basic caller and connection information.

Build the project with CMake:

```bash
mkdir build && cd build
cmake ..
make
./doc_sys
```
