from __future__ import annotations

import sqlite3

from .case_data import CaseData


def open_database(path: str) -> sqlite3.Connection:
    """Open or create an SQLite database."""
    return sqlite3.connect(path)


def create_case_table(conn: sqlite3.Connection) -> None:
    """Ensure that the cases table exists."""
    cur = conn.cursor()
    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS cases (
            caseId TEXT PRIMARY KEY,
            titleBriefDesc TEXT,
            descriptionPhoneCall TEXT,
            caseIdRelated TEXT,
            callerName TEXT,
            companyName TEXT,
            dongle TEXT,
            subscriptionId TEXT,
            officeNumber TEXT,
            cellphone TEXT,
            email TEXT,
            teamviewerId TEXT,
            teamviewerPassword TEXT,
            triosModuleVersion TEXT,
            uniteVersion TEXT,
            uniteCompanyId TEXT,
            helpJuiceOrJiraUsed TEXT,
            baseSerialNumber TEXT,
            scannerSerialNumber TEXT,
            scannerModel TEXT,
            scannerBroken INTEGER,
            relatedCaseLast30Days INTEGER,
            happenedLast30Days INTEGER,
            possibleCause TEXT,
            performanceIssue INTEGER,
            anyUpdate INTEGER,
            manualAdditional TEXT,
            reason TEXT,
            solution TEXT,
            recommendation TEXT,
            hjTutorial INTEGER,
            restartComputer INTEGER,
            scanTime INTEGER,
            recommendationEmail TEXT,
            serviceTag TEXT,
            pcModel TEXT,
            windowsVersion TEXT,
            biosVersion TEXT,
            graphicsCard TEXT,
            processor TEXT,
            warranty TEXT,
            logsTaken INTEGER,
            screenshotsTaken INTEGER,
            recapEmailSent INTEGER
        )
        """
    )
    conn.commit()


def insert_case_data(conn: sqlite3.Connection, d: CaseData) -> None:
    """Insert a case record into the database."""
    cur = conn.cursor()
    cur.execute(
        """
        INSERT INTO cases (
            caseId, titleBriefDesc, descriptionPhoneCall, caseIdRelated,
            callerName, companyName, dongle, subscriptionId, officeNumber,
            cellphone, email, teamviewerId, teamviewerPassword, triosModuleVersion,
            uniteVersion, uniteCompanyId, helpJuiceOrJiraUsed, baseSerialNumber,
            scannerSerialNumber, scannerModel, scannerBroken, relatedCaseLast30Days,
            happenedLast30Days, possibleCause, performanceIssue, anyUpdate,
            manualAdditional, reason, solution, recommendation, hjTutorial,
            restartComputer, scanTime, recommendationEmail, serviceTag, pcModel,
            windowsVersion, biosVersion, graphicsCard, processor, warranty,
            logsTaken, screenshotsTaken, recapEmailSent
        ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
        """,
        (
            d.case_id,
            d.title_brief_desc,
            d.description_phone_call,
            d.case_id_related,
            d.caller_name,
            d.company_name,
            d.dongle,
            d.subscription_id,
            d.office_number,
            d.cellphone,
            d.email,
            d.teamviewer_id,
            d.teamviewer_password,
            d.trios_module_version,
            d.unite_version,
            d.unite_company_id,
            d.helpjuice_or_jira_used,
            d.base_serial_number,
            d.scanner_serial_number,
            d.scanner_model,
            int(d.scanner_broken),
            int(d.related_case_last_30_days),
            int(d.happened_last_30_days),
            d.possible_cause,
            int(d.performance_issue),
            int(d.any_update),
            d.manual_additional,
            d.reason,
            d.solution,
            d.recommendation,
            int(d.hj_tutorial),
            int(d.restart_computer),
            int(d.scan_time),
            d.recommendation_email,
            d.service_tag,
            d.pc_model,
            d.windows_version,
            d.bios_version,
            d.graphics_card,
            d.processor,
            d.warranty,
            int(d.logs_taken),
            int(d.screenshots_taken),
            int(d.recap_email_sent),
        ),
    )
    conn.commit()
