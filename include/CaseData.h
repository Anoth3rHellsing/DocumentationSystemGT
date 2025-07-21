#ifndef CASE_DATA_H
#define CASE_DATA_H

#include <string>
#include <ctime>

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

    std::string buildTitle() const {
        return "||" + companyName + "|SID" + subscriptionId + "|" + titleBriefDesc + "|" + caseId;
    }

    std::string buildPhonecallTitle() const {
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        tm = *std::localtime(&t);
#endif
        char buf[16];
        std::strftime(buf, sizeof(buf), "%Y%m%d", &tm);
        return std::string("PHONECALL") + buf;
    }

    std::string buildPhonecallNote() const {
        std::string note;
        note += "Caller name:\t" + callerName + "\n";
        note += "Description:\t" + descriptionPhoneCall + "\n";
        note += "Dongle Number:\t" + dongle + "\n";
        note += "Phone Number:\t" + cellphone + "\n";
        note += "TeamViewerID:\t" + teamviewerId + "\n";
        note += "TeamViewer Password:\t" + teamviewerPassword + "\n";
        note += "Email:\t" + email;
        return note;
    }

    enum class InternalNoteVariation {
        HelpjuiceUsed,
        LogsAttached,
        CouldNotAttachLogs
    };

    std::string buildInternalNoteTitle() const {
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        tm = *std::localtime(&t);
#endif
        char buf[16];
        std::strftime(buf, sizeof(buf), "%Y%m%d", &tm);
        return std::string("INT-") + buf;
    }

    std::string buildInternalNote(InternalNoteVariation variation,
                                  const std::string& info = "") const {
        switch (variation) {
        case InternalNoteVariation::HelpjuiceUsed:
            return "Helpjuice Used:\t" + info;
        case InternalNoteVariation::LogsAttached:
            return "Logs:\tLogs attached (Zip Folder must be attached)";
        case InternalNoteVariation::CouldNotAttachLogs:
        default:
            return "Could not attach logs: " + info;
        }
    }
}; 

#endif // CASE_DATA_H
