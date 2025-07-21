#include <iostream>
#include "CaseData.h"
#include "Database.h"

int main() {
    CaseData d;
    d.caseId = "1234";
    d.companyName = "ExampleCorp";
    d.subscriptionId = "5678";
    d.titleBriefDesc = "Network issue";

    sqlite3* db = openDatabase("cases.db");
    if (!db) return 1;
    if (!createCaseTable(db)) return 1;

    if (!insertCaseData(db, d)) {
        sqlite3_close(db);
        return 1;
    }

    std::cout << "Stored case with title: " << d.buildTitle() << std::endl;

    std::cout << "Phonecall title: " << d.buildPhonecallTitle() << std::endl;
    std::cout << d.buildPhonecallNote() << std::endl;

    sqlite3_close(db);
    return 0;
}
