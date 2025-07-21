#include "Database.h"
#include <cassert>
#include <cstdio>
#include <sqlite3.h>

int main() {
    const char* path = "test.db";
    sqlite3* db = openDatabase(path);
    assert(db && "openDatabase failed");

    bool ok = createCaseTable(db);
    assert(ok && "createCaseTable failed");

    CaseData d{};
    d.caseId = "1";
    d.titleBriefDesc = "test";
    d.companyName = "TestCo";
    d.subscriptionId = "0";

    assert(insertCaseData(db, d) && "insertCaseData failed");

    sqlite3_close(db);
    std::remove(path);
    return 0;
}
