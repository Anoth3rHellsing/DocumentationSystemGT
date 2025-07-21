#include <iostream>
#include "CaseData.h"

int main() {
    CaseData caseData;
    caseData.caseId = "";
    caseData.titleBriefDesc = "";
    // Additional fields can be populated here or via input logic

    std::cout << "Case ID: " << caseData.caseId << std::endl;
    std::cout << "Title: " << caseData.titleBriefDesc << std::endl;
    return 0;
}
