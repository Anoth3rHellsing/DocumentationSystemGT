from __future__ import annotations

import tkinter as tk
from tkinter import ttk, messagebox

from .case_data import CaseData
from .case_data import CaseData as CD
from .database import open_database, create_case_table, insert_case_data


class App(tk.Tk):
    """Tkinter GUI for the documentation system."""

    def __init__(self) -> None:
        super().__init__()
        self.title("Documentation System")
        self.data = CaseData()

        self._build_widgets()
        self.update_preview()

    def _build_widgets(self) -> None:
        frame = ttk.Frame(self)
        frame.pack(fill=tk.BOTH, expand=True)

        # Text variables
        self.case_id = tk.StringVar()
        self.company = tk.StringVar()
        self.subscription = tk.StringVar()
        self.title_brief = tk.StringVar()
        self.caller = tk.StringVar()
        self.description = tk.StringVar()
        self.dongle = tk.StringVar()
        self.phone = tk.StringVar()
        self.teamviewer_id = tk.StringVar()
        self.teamviewer_pass = tk.StringVar()
        self.email = tk.StringVar()
        self.logs_var = tk.BooleanVar()
        self.screenshots_var = tk.BooleanVar()
        self.recap_var = tk.BooleanVar()
        self.internal_var = tk.StringVar(value="Helpjuice Used")
        self.internal_info = tk.StringVar()
        self.antivirus_var = tk.BooleanVar()
        self.antivirus_name = tk.StringVar()
        self.firewall_var = tk.BooleanVar()
        self.update_var = tk.BooleanVar()
        self.update_from = tk.StringVar()
        self.update_to = tk.StringVar()
        self.related_case_var = tk.BooleanVar()
        self.related_case_number = tk.StringVar()

        # Form layout
        form = ttk.Frame(frame)
        form.grid(row=0, column=0, sticky="nsew")
        for i, (text, var) in enumerate(
            [
                ("Case ID", self.case_id),
                ("Company", self.company),
                ("Subscription ID", self.subscription),
                ("Title", self.title_brief),
                ("Caller", self.caller),
                ("Description", self.description),
                ("Dongle", self.dongle),
                ("Phone", self.phone),
                ("TeamViewer ID", self.teamviewer_id),
                ("TeamViewer Pass", self.teamviewer_pass),
                ("Email", self.email),
            ]
        ):
            ttk.Label(form, text=text).grid(row=i, column=0, sticky="w")
            entry = ttk.Entry(form, textvariable=var)
            entry.grid(row=i, column=1, sticky="ew")
            entry.bind("<KeyRelease>", lambda e: self.update_preview())
        form.columnconfigure(1, weight=1)

        row = 11
        ttk.Checkbutton(
            form, text="Logs taken", variable=self.logs_var, command=self.update_preview
        ).grid(row=row, column=0, columnspan=2, sticky="w")
        row += 1
        ttk.Checkbutton(
            form,
            text="Screenshots taken",
            variable=self.screenshots_var,
            command=self.update_preview,
        ).grid(row=row, column=0, columnspan=2, sticky="w")
        row += 1
        ttk.Checkbutton(
            form,
            text="Recap email sent",
            variable=self.recap_var,
            command=self.update_preview,
        ).grid(row=row, column=0, columnspan=2, sticky="w")
        row += 1
        ttk.Label(form, text="Internal Note").grid(row=row, column=0, sticky="w")
        combo = ttk.Combobox(
            form,
            textvariable=self.internal_var,
            values=["Helpjuice Used", "Logs Attached", "Could Not Attach Logs"],
            state="readonly",
        )
        combo.grid(row=row, column=1, sticky="ew")
        combo.bind("<<ComboboxSelected>>", lambda e: self.update_preview())
        row += 1
        ttk.Label(form, text="Extra Info").grid(row=row, column=0, sticky="w")
        info_entry = ttk.Entry(form, textvariable=self.internal_info)
        info_entry.grid(row=row, column=1, sticky="ew")
        info_entry.bind("<KeyRelease>", lambda e: self.update_preview())
        row += 1
        add_frame = ttk.LabelFrame(form, text="Additional Information")
        add_frame.grid(row=row, column=0, columnspan=2, sticky="ew")
        ttk.Checkbutton(
            add_frame,
            text="Customer uses antivirus?",
            variable=self.antivirus_var,
            command=self.update_preview,
        ).grid(row=0, column=0, sticky="w")
        av_entry = ttk.Entry(add_frame, textvariable=self.antivirus_name)
        av_entry.grid(row=0, column=1, columnspan=2, sticky="ew")
        av_entry.bind("<KeyRelease>", lambda e: self.update_preview())
        ttk.Checkbutton(
            add_frame,
            text="Firewalls are turned on?",
            variable=self.firewall_var,
            command=self.update_preview,
        ).grid(row=1, column=0, columnspan=3, sticky="w")
        ttk.Checkbutton(
            add_frame,
            text="Any update was made?",
            variable=self.update_var,
            command=self.update_preview,
        ).grid(row=2, column=0, sticky="w")
        from_entry = ttk.Entry(add_frame, textvariable=self.update_from, width=10)
        from_entry.grid(row=2, column=1, sticky="ew")
        from_entry.bind("<KeyRelease>", lambda e: self.update_preview())
        to_entry = ttk.Entry(add_frame, textvariable=self.update_to, width=10)
        to_entry.grid(row=2, column=2, sticky="ew")
        to_entry.bind("<KeyRelease>", lambda e: self.update_preview())
        ttk.Checkbutton(
            add_frame,
            text="Is there any related case?",
            variable=self.related_case_var,
            command=self.update_preview,
        ).grid(row=3, column=0, sticky="w")
        rel_entry = ttk.Entry(add_frame, textvariable=self.related_case_number)
        rel_entry.grid(row=3, column=1, columnspan=2, sticky="ew")
        rel_entry.bind("<KeyRelease>", lambda e: self.update_preview())
        add_frame.columnconfigure(1, weight=1)
        add_frame.columnconfigure(2, weight=1)
        row += 1
        ttk.Button(form, text="Save Case", command=self.save_case).grid(
            row=row, column=0, columnspan=2, pady=5
        )

        # Preview box
        self.preview = tk.Text(frame, width=50)
        self.preview.grid(row=0, column=1, sticky="nsew", padx=5)
        self.preview.configure(state="disabled")

        frame.columnconfigure(0, weight=1)
        frame.columnconfigure(1, weight=1)

    def update_preview(self) -> None:
        self.data.case_id = self.case_id.get()
        self.data.company_name = self.company.get()
        self.data.subscription_id = self.subscription.get()
        self.data.title_brief_desc = self.title_brief.get()
        self.data.caller_name = self.caller.get()
        self.data.description_phone_call = self.description.get()
        self.data.dongle = self.dongle.get()
        self.data.cellphone = self.phone.get()
        self.data.teamviewer_id = self.teamviewer_id.get()
        self.data.teamviewer_password = self.teamviewer_pass.get()
        self.data.email = self.email.get()
        self.data.logs_taken = self.logs_var.get()
        self.data.screenshots_taken = self.screenshots_var.get()
        self.data.recap_email_sent = self.recap_var.get()
        self.data.customer_uses_antivirus = self.antivirus_var.get()
        self.data.antivirus = self.antivirus_name.get()
        self.data.firewalls_on = self.firewall_var.get()
        self.data.any_update = self.update_var.get()
        self.data.update_from_version = self.update_from.get()
        self.data.update_to_version = self.update_to.get()
        self.data.has_related_case = self.related_case_var.get()
        self.data.case_id_related = self.related_case_number.get()

        var_map = {
            "Helpjuice Used": CD.InternalNoteVariation.HELPJUICE_USED,
            "Logs Attached": CD.InternalNoteVariation.LOGS_ATTACHED,
            "Could Not Attach Logs": CD.InternalNoteVariation.COULD_NOT_ATTACH_LOGS,
        }
        var = var_map[self.internal_var.get()]
        info = self.internal_info.get()

        preview = (
            f"Case Title:\n{self.data.build_title()}\n\n"
            f"Phonecall Title:\n{self.data.build_phonecall_title()}\n"
            f"{self.data.build_phonecall_note()}\n\n"
            f"Internal Note Title:\n{self.data.build_internal_note_title()}\n"
            f"{self.data.build_internal_note(var, info)}\n\n"
            f"Mission Critical Checklist:\n{self.data.build_mission_critical_checklist()}\n\n"
            f"Additional Information:\n{self.data.build_additional_information_table()}"
        )
        self.preview.configure(state="normal")
        self.preview.delete("1.0", tk.END)
        self.preview.insert(tk.END, preview)
        self.preview.configure(state="disabled")

    def save_case(self) -> None:
        self.update_preview()
        try:
            conn = open_database("cases.db")
            create_case_table(conn)
            insert_case_data(conn, self.data)
            conn.close()
        except Exception as exc:  # pragma: no cover - simple error popup
            messagebox.showerror("Error", str(exc))
            return
        messagebox.showinfo("Success", "Case saved to database")


if __name__ == "__main__":
    app = App()
    app.mainloop()
