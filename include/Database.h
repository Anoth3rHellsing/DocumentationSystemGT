#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "CaseData.h"
#include <sqlite3.h>

sqlite3* openDatabase(const std::string& path);
bool createCaseTable(sqlite3* db);
bool insertCaseData(sqlite3* db, const CaseData& data);

#endif // DATABASE_H
