#ifndef CASE_DATA_H
#define CASE_DATA_H

#include <string>
#include <optional>

struct CaseData {
    // Basic case identification
    std::string caseId;
    std::string titleBriefDesc;
    std::string descriptionPhoneCall;
    std::string caseIdRelated;

    // Customer information
    std::string callerName;
    std::string companyName;
    std::string dongle;
    std::string subscriptionId;
    std::string officeNumber;
    std::string cellphone;
    std::string email;
    std::string teamviewerId;
    std::string teamviewerPassword;

    // Software versions
    std::string triosModuleVersion;
    std::string uniteVersion;
    std::string uniteCompanyId;
    std::string helpJuiceOrJiraUsed;

    // Scanner information
    std::string baseSerialNumber;
    std::string scannerSerialNumber;
    std::string scannerModel;
    bool scannerBroken = false;

    // Automated additional information
    bool relatedCaseLast30Days = false;
    bool happenedLast30Days = false;
    std::string possibleCause;
    bool performanceIssue = false;
    bool anyUpdate = false;
    std::string manualAdditional;

    // Automated conclusion
    std::string reason;
    std::string solution;
    std::string recommendation;
    bool hjTutorial = false;
    bool restartComputer = false;
    bool scanTime = false;
    std::string recommendationEmail;

    // PC information
    std::string serviceTag;
    std::string pcModel;
    std::string windowsVersion;
    std::string biosVersion;
    std::string graphicsCard;
    std::string processor;
    std::string warranty;
};

#endif // CASE_DATA_H
