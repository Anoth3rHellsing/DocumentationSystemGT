#include "CaseData.h"
#include "Database.h"
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QWidget {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
    setWindowTitle("Case Entry");

    // Create widgets
    caseIdEdit = new QLineEdit;
    caseIdEdit->setPlaceholderText("Enter case ID");
    companyEdit = new QLineEdit;
    companyEdit->setPlaceholderText("Company name");
    subscriptionEdit = new QLineEdit;
    subscriptionEdit->setPlaceholderText("Subscription ID");
    titleBriefEdit = new QLineEdit;
    titleBriefEdit->setPlaceholderText("Case title");
    callerEdit = new QLineEdit;
    callerEdit->setPlaceholderText("Caller name");
    descriptionEdit = new QLineEdit;
    descriptionEdit->setPlaceholderText("Description");
    dongleEdit = new QLineEdit;
    dongleEdit->setPlaceholderText("Dongle");
    phoneEdit = new QLineEdit;
    phoneEdit->setPlaceholderText("Phone number");
    teamviewerIdEdit = new QLineEdit;
    teamviewerIdEdit->setPlaceholderText("TeamViewer ID");
    teamviewerPassEdit = new QLineEdit;
    teamviewerPassEdit->setPlaceholderText("TeamViewer password");
    emailEdit = new QLineEdit;
    emailEdit->setPlaceholderText("Email");
    logsCheck = new QCheckBox("Logs taken");
    screenshotsCheck = new QCheckBox("Screenshots taken");
    recapCheck = new QCheckBox("Recap email sent");
    internalCombo = new QComboBox;
    internalCombo->addItem("Helpjuice Used");
    internalCombo->addItem("Logs Attached");
    internalCombo->addItem("Could Not Attach Logs");
    internalInfoEdit = new QLineEdit;
    internalInfoEdit->setPlaceholderText("Extra info");
    QPushButton *saveBtn = new QPushButton("Save Case");

    previewEdit = new QTextEdit;
    previewEdit->setReadOnly(true);
    previewEdit->setPlaceholderText("Case preview");

    // Group layouts for better organization
    QGroupBox *caseGroup = new QGroupBox("Case Info");
    QFormLayout *caseForm = new QFormLayout;
    caseForm->addRow("Case ID", caseIdEdit);
    caseForm->addRow("Company", companyEdit);
    caseForm->addRow("Subscription ID", subscriptionEdit);
    caseForm->addRow("Title", titleBriefEdit);
    caseForm->addRow("Description", descriptionEdit);
    caseForm->addRow("Dongle", dongleEdit);
    caseGroup->setLayout(caseForm);

    QGroupBox *contactGroup = new QGroupBox("Contact");
    QFormLayout *contactForm = new QFormLayout;
    contactForm->addRow("Caller", callerEdit);
    contactForm->addRow("Phone", phoneEdit);
    contactForm->addRow("TeamViewer ID", teamviewerIdEdit);
    contactForm->addRow("TeamViewer Pass", teamviewerPassEdit);
    contactForm->addRow("Email", emailEdit);
    contactGroup->setLayout(contactForm);

    QGroupBox *internalGroup = new QGroupBox("Internal Note");
    QFormLayout *internalForm = new QFormLayout;
    internalForm->addRow("Type", internalCombo);
    internalForm->addRow("Extra Info", internalInfoEdit);
    internalGroup->setLayout(internalForm);

    QGroupBox *optionsGroup = new QGroupBox("Options");
    QVBoxLayout *optionsLayout = new QVBoxLayout;
    optionsLayout->addWidget(logsCheck);
    optionsLayout->addWidget(screenshotsCheck);
    optionsLayout->addWidget(recapCheck);
    optionsGroup->setLayout(optionsLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(caseGroup);
    leftLayout->addWidget(contactGroup);
    leftLayout->addWidget(internalGroup);
    leftLayout->addWidget(optionsGroup);
    leftLayout->addWidget(saveBtn);
    leftLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addWidget(previewEdit, 1);
    setLayout(mainLayout);

    connect(caseIdEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(companyEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(subscriptionEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(titleBriefEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(callerEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(descriptionEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(dongleEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(phoneEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(teamviewerIdEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(teamviewerPassEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(emailEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
    connect(logsCheck, &QCheckBox::stateChanged, this,
            &MainWindow::updatePreview);
    connect(screenshotsCheck, &QCheckBox::stateChanged, this,
            &MainWindow::updatePreview);
    connect(recapCheck, &QCheckBox::stateChanged, this,
            &MainWindow::updatePreview);
    connect(internalCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::updatePreview);
    connect(internalInfoEdit, &QLineEdit::textChanged, this,
            &MainWindow::updatePreview);
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

    CaseData::InternalNoteVariation var =
        CaseData::InternalNoteVariation::HelpjuiceUsed;
    switch (internalCombo->currentIndex()) {
    case 0:
      var = CaseData::InternalNoteVariation::HelpjuiceUsed;
      break;
    case 1:
      var = CaseData::InternalNoteVariation::LogsAttached;
      break;
    case 2:
      var = CaseData::InternalNoteVariation::CouldNotAttachLogs;
      break;
    }
    std::string info = internalInfoEdit->text().toStdString();

    std::string preview;
    preview += "Case Title:\n" + data.buildTitle() + "\n\n";
    preview += "Phonecall Title:\n" + data.buildPhonecallTitle() + "\n";
    preview += data.buildPhonecallNote() + "\n\n";
    preview += "Internal Note Title:\n" + data.buildInternalNoteTitle() + "\n";
    preview += data.buildInternalNote(var, info) + "\n\n";
    preview +=
        "Mission Critical Checklist:\n" + data.buildMissionCriticalChecklist();

    previewEdit->setPlainText(QString::fromStdString(preview));
  }

  void saveCase() {
    updatePreview();
    sqlite3 *db = openDatabase("cases.db");
    if (!db) {
      QMessageBox::critical(this, "Error", "Failed to open database");
      return;
    }
    if (!createCaseTable(db)) {
      QMessageBox::critical(this, "Error", "Failed to create table");
      sqlite3_close(db);
      return;
    }
    if (!insertCaseData(db, data)) {
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
