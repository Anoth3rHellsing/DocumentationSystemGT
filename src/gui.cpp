#include <QApplication>
#include <QComboBox>
#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include "CaseData.h"
#include "Database.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        // Create widgets
        caseIdEdit = new QLineEdit;
        companyEdit = new QLineEdit;
        subscriptionEdit = new QLineEdit;
        titleBriefEdit = new QLineEdit;
        callerEdit = new QLineEdit;
        descriptionEdit = new QLineEdit;
        dongleEdit = new QLineEdit;
        phoneEdit = new QLineEdit;
        teamviewerIdEdit = new QLineEdit;
        teamviewerPassEdit = new QLineEdit;
        emailEdit = new QLineEdit;
        logsCheck = new QCheckBox("Logs taken");
        screenshotsCheck = new QCheckBox("Screenshots taken");
        recapCheck = new QCheckBox("Recap email sent");
        internalCombo = new QComboBox;
        internalCombo->addItem("Helpjuice Used");
        internalCombo->addItem("Logs Attached");
        internalCombo->addItem("Could Not Attach Logs");
        internalInfoEdit = new QLineEdit;
        QPushButton *saveBtn = new QPushButton("Save Case");

        previewEdit = new QTextEdit;
        previewEdit->setReadOnly(true);

        // Layouts
        QFormLayout *form = new QFormLayout;
        form->addRow("Case ID", caseIdEdit);
        form->addRow("Company", companyEdit);
        form->addRow("Subscription ID", subscriptionEdit);
        form->addRow("Title", titleBriefEdit);
        form->addRow("Caller", callerEdit);
        form->addRow("Description", descriptionEdit);
        form->addRow("Dongle", dongleEdit);
        form->addRow("Phone", phoneEdit);
        form->addRow("TeamViewer ID", teamviewerIdEdit);
        form->addRow("TeamViewer Pass", teamviewerPassEdit);
        form->addRow("Email", emailEdit);
        form->addRow(logsCheck);
        form->addRow(screenshotsCheck);
        form->addRow(recapCheck);
        form->addRow("Internal Note", internalCombo);
        form->addRow("Extra Info", internalInfoEdit);
        form->addRow(saveBtn);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addLayout(form, 1);
        mainLayout->addWidget(previewEdit, 1);
        setLayout(mainLayout);

        connect(caseIdEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(companyEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(subscriptionEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(titleBriefEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(callerEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(descriptionEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(dongleEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(phoneEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(teamviewerIdEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(teamviewerPassEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(emailEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(logsCheck, &QCheckBox::stateChanged, this, &MainWindow::updatePreview);
        connect(screenshotsCheck, &QCheckBox::stateChanged, this, &MainWindow::updatePreview);
        connect(recapCheck, &QCheckBox::stateChanged, this, &MainWindow::updatePreview);
        connect(internalCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::updatePreview);
        connect(internalInfoEdit, &QLineEdit::textChanged, this, &MainWindow::updatePreview);
        connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveCase);

        updatePreview();
    }

private slots:
    void updatePreview() {
        data.caseId = caseIdEdit->text().toStdString();
        data.companyName = companyEdit->text().toStdString();
        data.subscriptionId = subscriptionEdit->text().toStdString();
        data.titleBriefDesc = titleBriefEdit->text().toStdString();
        data.callerName = callerEdit->text().toStdString();
        data.descriptionPhoneCall = descriptionEdit->text().toStdString();
        data.dongle = dongleEdit->text().toStdString();
        data.cellphone = phoneEdit->text().toStdString();
        data.teamviewerId = teamviewerIdEdit->text().toStdString();
        data.teamviewerPassword = teamviewerPassEdit->text().toStdString();
        data.email = emailEdit->text().toStdString();
        data.logsTaken = logsCheck->isChecked();
        data.screenshotsTaken = screenshotsCheck->isChecked();
        data.recapEmailSent = recapCheck->isChecked();

        CaseData::InternalNoteVariation var = CaseData::InternalNoteVariation::HelpjuiceUsed;
        switch(internalCombo->currentIndex()) {
        case 0: var = CaseData::InternalNoteVariation::HelpjuiceUsed; break;
        case 1: var = CaseData::InternalNoteVariation::LogsAttached; break;
        case 2: var = CaseData::InternalNoteVariation::CouldNotAttachLogs; break;
        }
        std::string info = internalInfoEdit->text().toStdString();

        std::string preview;
        preview += "Case Title:\n" + data.buildTitle() + "\n\n";
        preview += "Phonecall Title:\n" + data.buildPhonecallTitle() + "\n";
        preview += data.buildPhonecallNote() + "\n\n";
        preview += "Internal Note Title:\n" + data.buildInternalNoteTitle() + "\n";
        preview += data.buildInternalNote(var, info) + "\n\n";
        preview += "Mission Critical Checklist:\n" + data.buildMissionCriticalChecklist();

        previewEdit->setPlainText(QString::fromStdString(preview));
    }

    void saveCase() {
        updatePreview();
        sqlite3* db = openDatabase("cases.db");
        if(!db) {
            QMessageBox::critical(this, "Error", "Failed to open database");
            return;
        }
        if(!createCaseTable(db)) {
            QMessageBox::critical(this, "Error", "Failed to create table");
            sqlite3_close(db);
            return;
        }
        if(!insertCaseData(db, data)) {
            QMessageBox::critical(this, "Error", "Failed to insert case");
            sqlite3_close(db);
            return;
        }
        sqlite3_close(db);
        QMessageBox::information(this, "Success", "Case saved to database");
    }

private:
    CaseData data;
    QLineEdit *caseIdEdit;
    QLineEdit *companyEdit;
    QLineEdit *subscriptionEdit;
    QLineEdit *titleBriefEdit;
    QLineEdit *callerEdit;
    QLineEdit *descriptionEdit;
    QLineEdit *dongleEdit;
    QLineEdit *phoneEdit;
    QLineEdit *teamviewerIdEdit;
    QLineEdit *teamviewerPassEdit;
    QLineEdit *emailEdit;
    QCheckBox *logsCheck;
    QCheckBox *screenshotsCheck;
    QCheckBox *recapCheck;
    QComboBox *internalCombo;
    QLineEdit *internalInfoEdit;
    QTextEdit *previewEdit;
};

#include "gui.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
