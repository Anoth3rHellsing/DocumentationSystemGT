#include "Database.h"
#include <iostream>

sqlite3* openDatabase(const std::string& path) {
    sqlite3* db = nullptr;
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        if (db)
            sqlite3_close(db);
        return nullptr;
    }
    return db;
}

bool createCaseTable(sqlite3* db) {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS cases ("
        "caseId TEXT PRIMARY KEY,"
        "titleBriefDesc TEXT,"
        "descriptionPhoneCall TEXT,"
        "caseIdRelated TEXT,"
        "callerName TEXT,"
        "companyName TEXT,"
        "dongle TEXT,"
        "subscriptionId TEXT,"
        "officeNumber TEXT,"
        "cellphone TEXT,"
        "email TEXT,"
        "teamviewerId TEXT,"
        "teamviewerPassword TEXT,"
        "triosModuleVersion TEXT,"
        "uniteVersion TEXT,"
        "uniteCompanyId TEXT,"
        "helpJuiceOrJiraUsed TEXT,"
        "baseSerialNumber TEXT,"
        "scannerSerialNumber TEXT,"
        "scannerModel TEXT,"
        "scannerBroken INTEGER,"
        "relatedCaseLast30Days INTEGER,"
        "happenedLast30Days INTEGER,"
        "possibleCause TEXT,"
        "performanceIssue INTEGER,"
        "anyUpdate INTEGER,"
        "manualAdditional TEXT,"
        "reason TEXT,"
        "solution TEXT,"
        "recommendation TEXT,"
        "hjTutorial INTEGER,"
        "restartComputer INTEGER,"
        "scanTime INTEGER,"
        "recommendationEmail TEXT,"
        "serviceTag TEXT,"
        "pcModel TEXT,"
        "windowsVersion TEXT,"
        "biosVersion TEXT,"
        "graphicsCard TEXT,"
        "processor TEXT,"
        "warranty TEXT,"
        "logsTaken INTEGER,"
        "screenshotsTaken INTEGER,"
        "recapEmailSent INTEGER"
        ");";

    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::cerr << "Failed to create table: " << err << std::endl;
        sqlite3_free(err);
        return false;
    }
    return true;
}

bool insertCaseData(sqlite3* db, const CaseData& d) {
    const char* sql =
        "INSERT INTO cases (caseId, titleBriefDesc, descriptionPhoneCall, caseIdRelated, callerName, companyName, dongle, subscriptionId, officeNumber, cellphone, email, teamviewerId, teamviewerPassword, triosModuleVersion, uniteVersion, uniteCompanyId, helpJuiceOrJiraUsed, baseSerialNumber, scannerSerialNumber, scannerModel, scannerBroken, relatedCaseLast30Days, happenedLast30Days, possibleCause, performanceIssue, anyUpdate, manualAdditional, reason, solution, recommendation, hjTutorial, restartComputer, scanTime, recommendationEmail, serviceTag, pcModel, windowsVersion, biosVersion, graphicsCard, processor, warranty, logsTaken, screenshotsTaken, recapEmailSent) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        return false;
    }

    int idx = 1;
    auto bindText = [&](const std::string& val) {
        sqlite3_bind_text(stmt, idx++, val.c_str(), -1, SQLITE_TRANSIENT);
    };
    auto bindBool = [&](bool val) {
        sqlite3_bind_int(stmt, idx++, val ? 1 : 0);
    };

    bindText(d.caseId);
    bindText(d.titleBriefDesc);
    bindText(d.descriptionPhoneCall);
    bindText(d.caseIdRelated);
    bindText(d.callerName);
    bindText(d.companyName);
    bindText(d.dongle);
    bindText(d.subscriptionId);
    bindText(d.officeNumber);
    bindText(d.cellphone);
    bindText(d.email);
    bindText(d.teamviewerId);
    bindText(d.teamviewerPassword);
    bindText(d.triosModuleVersion);
    bindText(d.uniteVersion);
    bindText(d.uniteCompanyId);
    bindText(d.helpJuiceOrJiraUsed);
    bindText(d.baseSerialNumber);
    bindText(d.scannerSerialNumber);
    bindText(d.scannerModel);
    bindBool(d.scannerBroken);
    bindBool(d.relatedCaseLast30Days);
    bindBool(d.happenedLast30Days);
    bindText(d.possibleCause);
    bindBool(d.performanceIssue);
    bindBool(d.anyUpdate);
    bindText(d.manualAdditional);
    bindText(d.reason);
    bindText(d.solution);
    bindText(d.recommendation);
    bindBool(d.hjTutorial);
    bindBool(d.restartComputer);
    bindBool(d.scanTime);
    bindText(d.recommendationEmail);
    bindText(d.serviceTag);
    bindText(d.pcModel);
    bindText(d.windowsVersion);
    bindText(d.biosVersion);
    bindText(d.graphicsCard);
    bindText(d.processor);
    bindText(d.warranty);
    bindBool(d.logsTaken);
    bindBool(d.screenshotsTaken);
    bindBool(d.recapEmailSent);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    if (!ok) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return ok;
}

