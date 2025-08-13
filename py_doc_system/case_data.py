from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime
from enum import Enum


@dataclass
class CaseData:
    """Container for CRM case information."""

    # Basic case identification
    case_id: str = ""
    title_brief_desc: str = ""
    description_phone_call: str = ""
    case_id_related: str = ""

    # Additional information
    customer_uses_antivirus: bool = False
    antivirus: str = ""
    firewalls_on: bool = False
    any_update: bool = False
    update_from_version: str = ""
    update_to_version: str = ""
    has_related_case: bool = False

    # Customer information
    caller_name: str = ""
    company_name: str = ""
    dongle: str = ""
    subscription_id: str = ""
    office_number: str = ""
    cellphone: str = ""
    email: str = ""
    teamviewer_id: str = ""
    teamviewer_password: str = ""

    # Software versions
    trios_module_version: str = ""
    unite_version: str = ""
    unite_company_id: str = ""
    helpjuice_or_jira_used: str = ""

    # Scanner information
    base_serial_number: str = ""
    scanner_serial_number: str = ""
    scanner_model: str = ""
    scanner_broken: bool = False

    # Automated additional information
    related_case_last_30_days: bool = False
    happened_last_30_days: bool = False
    possible_cause: str = ""
    performance_issue: bool = False
    manual_additional: str = ""

    # Automated conclusion
    reason: str = ""
    solution: str = ""
    recommendation: str = ""
    hj_tutorial: bool = False
    restart_computer: bool = False
    scan_time: bool = False
    recommendation_email: str = ""

    # PC information
    service_tag: str = ""
    pc_model: str = ""
    windows_version: str = ""
    bios_version: str = ""
    graphics_card: str = ""
    processor: str = ""
    warranty: str = ""

    # Mission critical checklist
    logs_taken: bool = False
    screenshots_taken: bool = False
    recap_email_sent: bool = False

    def _today(self) -> str:
        return datetime.now().strftime("%Y%m%d")

    def build_mission_critical_checklist(self) -> str:
        to_str = lambda b: "TRUE" if b else "FALSE"
        return (
            f"Logs Taken?\t{to_str(self.logs_taken)}\n"
            f"Screenshots taken?\t{to_str(self.screenshots_taken)}\n"
            f"Recap Email sent?\t{to_str(self.recap_email_sent)}"
        )

    def build_title(self) -> str:
        return (
            f"||{self.company_name}|SID{self.subscription_id}|"
            f"{self.title_brief_desc}|{self.case_id}"
        )

    def build_phonecall_title(self) -> str:
        return f"PHONECALL{self._today()}"

    def build_phonecall_note(self) -> str:
        return (
            f"Caller name:\t{self.caller_name}\n"
            f"Description:\t{self.description_phone_call}\n"
            f"Dongle Number:\t{self.dongle}\n"
            f"Phone Number:\t{self.cellphone}\n"
            f"TeamViewerID:\t{self.teamviewer_id}\n"
            f"TeamViewer Password:\t{self.teamviewer_password}\n"
            f"Email:\t{self.email}"
        )

    class InternalNoteVariation(Enum):
        HELPJUICE_USED = 1
        LOGS_ATTACHED = 2
        COULD_NOT_ATTACH_LOGS = 3

    def build_internal_note_title(self) -> str:
        return f"INT-{self._today()}"

    def build_internal_note(
        self, variation: InternalNoteVariation, info: str = ""
    ) -> str:
        if variation is self.InternalNoteVariation.HELPJUICE_USED:
            return f"Helpjuice Used:\t{info}"
        if variation is self.InternalNoteVariation.LOGS_ATTACHED:
            return "Logs:\tLogs attached (Zip Folder must be attached)"
        return f"Could not attach logs: {info}"

    def build_additional_information_table(self) -> str:
        to_str = lambda b: "TRUE" if b else "FALSE"
        lines = [f"Customer uses antivirus?\t{to_str(self.customer_uses_antivirus)}"]
        if self.customer_uses_antivirus:
            lines.append(f"Antivirus\t{self.antivirus}")
        lines.append(f"Firewalls are turned on?\t{to_str(self.firewalls_on)}")
        lines.append(f"Any update was made?\t{to_str(self.any_update)}")
        if self.any_update:
            lines.append(
                f"Update from->to\t{self.update_from_version} -> {self.update_to_version}"
            )
        lines.append(f"Is there any related case?\t{to_str(self.has_related_case)}")
        if self.has_related_case:
            lines.append(f"Case number\t{self.case_id_related}")
        return "\n".join(lines)
