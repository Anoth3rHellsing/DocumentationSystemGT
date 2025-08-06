import sqlite3

import sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
import pytest

from py_doc_system.case_data import CaseData
from py_doc_system.case_data import CaseData as CD
from py_doc_system.database import create_case_table, insert_case_data, open_database


def test_case_data_builders():
    d = CaseData(
        case_id="1234",
        company_name="ExampleCorp",
        subscription_id="5678",
        title_brief_desc="Network issue",
        caller_name="Alice",
        description_phone_call="Lost connection",
        dongle="D1",
        cellphone="555-123",
        teamviewer_id="tv",
        teamviewer_password="pw",
        email="a@example.com",
        logs_taken=True,
        recap_email_sent=True,
    )
    assert d.build_title() == "||ExampleCorp|SID5678|Network issue|1234"
    assert "Logs Taken?\tTRUE" in d.build_mission_critical_checklist()
    assert d.build_internal_note_title().startswith("INT-")
    note = d.build_internal_note(CD.InternalNoteVariation.HELPJUICE_USED, "link")
    assert note == "Helpjuice Used:\tlink"


def test_database_insertion(tmp_path):
    db_path = tmp_path / "test.db"
    conn = open_database(str(db_path))
    create_case_table(conn)
    d = CaseData(case_id="1", company_name="TestCo", subscription_id="0", title_brief_desc="test")
    insert_case_data(conn, d)
    conn.close()
    assert db_path.exists()
    conn = sqlite3.connect(str(db_path))
    cur = conn.cursor()
    cur.execute("SELECT companyName FROM cases WHERE caseId='1'")
    row = cur.fetchone()
    assert row[0] == "TestCo"
    conn.close()
