#include "formatter.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->settingsManager = SettingsManager();
    ui->setupUi(this);

    this->defaultHeader = ui->invoice_header->toPlainText();
    this->defaultBody = ui->invoice_body->toPlainText();
    this->defaultFooter = ui->invoice_footer->toPlainText();

    this->setDatesToToday();
    this->setInvoiceNumberToCorresponding();
    this->loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatesToToday()
{
    this->ui->invoice_issued->setDate(QDate::currentDate());
    this->ui->invoice_term->setDate(QDate::currentDate());
    this->ui->invoice_selldate->setDate(QDate::currentDate());
}

void MainWindow::setInvoiceNumberToCorresponding()
{
    this->ui->invoice_nr->setText(QDate::currentDate().toString("yyyy/MM/X"));
}

void MainWindow::writeSettings()
{
    writeWindowSettings();
    writeSellerSettings();
    writeBuyerSettings();
    writeInvoiceSettings();
    writeTableSettings();
    writeGeneratorSettings();
    writeApplicationSettings();
}

void MainWindow::writeWindowSettings()
{
    settingsManager.setSetting("Window", "size", size());
}

void MainWindow::writeSellerSettings()
{
    QString settingName = QtEnumToString(AppArea::SELLER);
    settingsManager.setSetting(settingName, "name", ui->seller_name->text());
    settingsManager.setSetting(settingName, "nip", ui->seller_nip->text());
    settingsManager.setSetting(settingName, "account", ui->seller_account->text());
    settingsManager.setSetting(settingName, "bank", ui->seller_bank->text());
    settingsManager.setSetting(settingName, "street", ui->seller_street->text());
    settingsManager.setSetting(settingName, "city", ui->seller_city->text());
}

void MainWindow::writeBuyerSettings()
{
    QString settingName = QtEnumToString(AppArea::BUYER);
    settingsManager.setSetting(settingName, "name", ui->buyer_name->text());
    settingsManager.setSetting(settingName, "nip", ui->buyer_nip->text());
    settingsManager.setSetting(settingName, "city", ui->buyer_city->text());
    settingsManager.setSetting(settingName, "street", ui->buyer_street->text());
}

void MainWindow::writeInvoiceSettings()
{
    QString settingName = QtEnumToString(AppArea::INVOICE);
    settingsManager.setSetting(settingName, "type", ui->invoice_paymenttype->text());
    settingsManager.setSetting(settingName, "nrFormat", ui->invoice_nr->text());
    settingsManager.setSetting(settingName, "header", ui->invoice_header->toPlainText());
    settingsManager.setSetting(settingName, "body", ui->invoice_body->toPlainText());
    settingsManager.setSetting(settingName, "footer", ui->invoice_footer->toPlainText());
    settingsManager.setSetting(settingName, "logoPath", ui->invoice_logoPath->text());

}

void MainWindow::writeTableSettings()
{
    QString settingName = QtEnumToString(AppArea::TABLE);
    settingsManager.setSetting(settingName, "pkwiu", ui->table_pkwiu->isChecked());
    settingsManager.setSetting(settingName, "discount", ui->table_discount->isChecked());

}

void MainWindow::writeGeneratorSettings()
{
    QString settingName = QtEnumToString(AppArea::GENERATOR);
    settingsManager.setSetting(settingName, "filename", ui->generator_filename->text());
    settingsManager.setSetting(settingName, "sendmail", ui->generator_sendemail->isChecked());
    settingsManager.setSetting(settingName, "emailadress", ui->generator_emailadress->text());
    settingsManager.setSetting(settingName, "emailtitle", ui->generator_emailtitle->text());
    settingsManager.setSetting(settingName, "emailcontent", ui->generator_emailcontent->toPlainText());

}

void MainWindow::writeApplicationSettings()
{
    QString settingName = QtEnumToString(AppArea::SETTINGS);
    settingsManager.setSetting(settingName, "smtphost", ui->settings_smtphost->text());
    settingsManager.setSetting(settingName, "smtpport", ui->settings_smtpport->text());
    settingsManager.setSetting(settingName, "smtpnotsecure", ui->settings_smtpnotsecure->isChecked());
    settingsManager.setSetting(settingName, "smtpssl", ui->settings_smtpssl->isChecked());
    settingsManager.setSetting(settingName, "smtptls", ui->settings_smtptls->isChecked());
    settingsManager.setSetting(settingName, "smtpsender", ui->settings_smtpsender->text());
    settingsManager.setSetting(settingName, "smtpuser", ui->settings_smtpuser->text());
    settingsManager.setSetting(settingName, "smtppassword", ui->settings_smtppassword->text());
    settingsManager.setSetting(settingName, "autosave", ui->settings_autosave->isChecked());

}


void MainWindow::loadSettings()
{
    QSettings settings("ApproxTeam", "Fakturka");

    loadWindowSettings();
    loadSellerSettings();
    loadBuyerSettings();
    loadInvoiceSettings();
    loadTableSettings();
    loadGeneratorSettings();
    loadApplicationSettings();
}

void MainWindow::loadWindowSettings()
{
    resize(settingsManager.getSetting("Window", "size", QSize(1024, 780)).toSize());
}

void MainWindow::loadSellerSettings()
{
    QString settingName = QtEnumToString(AppArea::SELLER);
    ui->seller_name->setText(settingsManager.getSettingString(settingName, "name"));
    ui->seller_nip->setText(settingsManager.getSettingString(settingName, "nip"));
    ui->seller_account->setText(settingsManager.getSettingString(settingName, "account"));
    ui->seller_bank->setText(settingsManager.getSettingString(settingName, "bank"));
    ui->seller_street->setText(settingsManager.getSettingString(settingName, "street"));
    ui->seller_city->setText(settingsManager.getSettingString(settingName, "city"));
}

void MainWindow::loadBuyerSettings()
{
    QString settingName = QtEnumToString(AppArea::BUYER);
    ui->buyer_name->setText(settingsManager.getSettingString(settingName, "name"));
    ui->buyer_nip->setText(settingsManager.getSettingString(settingName, "nip"));
    ui->buyer_city->setText(settingsManager.getSettingString(settingName, "city"));
    ui->buyer_street->setText(settingsManager.getSettingString(settingName, "street"));

}

void MainWindow::loadInvoiceSettings()
{
    QString settingName = QtEnumToString(AppArea::INVOICE);
    ui->invoice_paymenttype->setText(settingsManager.getSettingString(settingName, "type"));
    ui->invoice_nr->setText(settingsManager.getSettingString(settingName, "nrFormat"));
    ui->invoice_header->setPlainText(settingsManager.getSettingString(settingName, "header"));
    ui->invoice_body->setPlainText(settingsManager.getSettingString(settingName, "body"));
    ui->invoice_footer->setPlainText(settingsManager.getSettingString(settingName, "footer"));
    ui->invoice_logoPath->setText(settingsManager.getSettingString(settingName, "logoPath"));
}



void MainWindow::loadTableSettings()
{
    QString settingName = QtEnumToString(AppArea::TABLE);
    ui->table_pkwiu->setChecked(settingsManager.getSettingBool(settingName, "pkwiu", QVariant(false)));
    ui->table_discount->setChecked(settingsManager.getSettingBool(settingName, "discount", QVariant(false)));

}

void MainWindow::loadGeneratorSettings()
{
    QString settingName = QtEnumToString(AppArea::GENERATOR);
    ui->generator_filename->setText(settingsManager.getSettingString(settingName, "filename"));
    ui->generator_sendemail->setChecked(settingsManager.getSettingBool(settingName, "sendmail"));
    ui->generator_emailadress->setText(settingsManager.getSettingString(settingName, "emailadress"));
    ui->generator_emailtitle->setText(settingsManager.getSettingString(settingName, "emailtitle"));
    ui->generator_emailcontent->setText(settingsManager.getSettingString(settingName, "emailcontent"));
}

void MainWindow::loadApplicationSettings()
{
    QString settingName = QtEnumToString(AppArea::SETTINGS);
    ui->settings_smtphost->setText(settingsManager.getSettingString(settingName, "smtphost"));
    ui->settings_smtpport->setText(settingsManager.getSettingString(settingName, "smtpport"));
    ui->settings_smtpnotsecure->setChecked(settingsManager.getSettingBool(settingName, "smtpnotsecure"));
    ui->settings_smtpssl->setChecked(settingsManager.getSettingBool(settingName, "smtpssl"));
    ui->settings_smtptls->setChecked(settingsManager.getSettingBool(settingName, "smtptls"));
    ui->settings_smtpsender->setText(settingsManager.getSettingString(settingName, "smtpsender"));
    ui->settings_smtpuser->setText(settingsManager.getSettingString(settingName, "smtpuser"));
    ui->settings_smtppassword->setText(settingsManager.getSettingString(settingName, "smtppassword"));
    ui->settings_autosave->setChecked(settingsManager.getSettingBool(settingName, "autosave"));

}

void MainWindow::incrementInvoiceNumberInSettings()
{
    QString settingName = QtEnumToString(AppArea::INVOICE);
    int currentMonthInvoiceNr = settingsManager.getSettingInt(settingName + "/NUMBER", getCurrentNameOfInvoiceNumber(), 1);
    currentMonthInvoiceNr++;
    settingsManager.setSetting(settingName + "/NUMBER", getCurrentNameOfInvoiceNumber(), QVariant(currentMonthInvoiceNr));

}

void MainWindow::generateInvoicePDFToFile(QString fileName)
{
    QString html = getFormattedDocHTML();

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10));

    document.print(&printer);


}

void MainWindow::removeTempFiles()
{

    QDir directory(".");
    directory.setNameFilters(QStringList() << "FAKTURKATEMP_*");
    directory.setFilter(QDir::Files);
    foreach(QString dirFile, directory.entryList())
    {
        directory.remove(dirFile);
    }

}

QString MainWindow::getFormattedInvoiceNr()
{
    QString settingName = QtEnumToString(AppArea::INVOICE);
    int currentMonthInvoiceNr = settingsManager.getSettingInt(settingName + "/NUMBER", getCurrentNameOfInvoiceNumber(), 1);
    QString currentFormat = ui->invoice_nr->text();
    QString currentYear = QDate::currentDate().toString("yyyy");
    QString currentMonth = QDate::currentDate().toString("MM");
    Formatter* formatter = new Formatter(currentFormat);
    return formatter->format("%yyyy%", currentYear)->format("%MM%", currentMonth)->format("%NR%", currentMonthInvoiceNr)->toString();

}

QString MainWindow::getFormattedFileName(QString invoiceNr)
{
    Formatter* formatter = new Formatter(ui->generator_filename->text());
    return formatter->format("%NRFAKTURY%", invoiceNr)->toString();

}

QString MainWindow::getCurrentNameOfInvoiceNumber()
{
    return QDate::currentDate().toString("yyyy-MM");
}

QString MainWindow::getUniqueName()
{
    return QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "");
}

QString MainWindow::getUniqueAppTempFile()
{
    return "FAKTURKATEMP_" + getUniqueName();
}

QString MainWindow::getUniqueAppPDFFile()
{
    return getUniqueAppTempFile() + ".pdf";
}

QString MainWindow::getFormattedDocHTML()
{
    return formatStringWithAvalaibleTags(ui->invoice_header->toPlainText()) + formatStringWithAvalaibleTags(ui->invoice_body->toPlainText()) + formatStringWithAvalaibleTags(ui->invoice_footer->toPlainText());
}

QString MainWindow::formatStringWithAvalaibleTags(QString value)
{
    Formatter* formatter = new Formatter(value);
    formatter->format("%NRFAKTURY%", getFormattedInvoiceNr());
    formatter->format("%LOGO%", ui->invoice_logoPath->text());
    formatter->format("%DATAWYSTAWIENIA%", ui->invoice_issued->text());
    formatter->format("%DATASPRZEDAZY%", ui->invoice_selldate->text());
    formatter->format("%TERMINPLATNOSCI%", ui->invoice_term->text());
    formatter->format("%TYPPLATNOSCI%", ui->invoice_paymenttype->text());

    return formatter->toString();
}



void MainWindow::addRowToTable()
{
    this->ui->table->insertRow(this->ui->table->rowCount());
}

void MainWindow::removeRowFromTable()
{
    QItemSelectionModel *select = this->ui->table->selectionModel();
    if(select->hasSelection()) {
        for(int index = 0; index < select->selectedRows().count(); index++) {
            QModelIndex selectedIndex = select->selectedRows().at(index);
            this->ui->table->removeRow(selectedIndex.row());
        }
    }
}

void MainWindow::togglePKWIUColumn(bool value)
{
    int myIndex = 1;
    if(value) {
        this->ui->table->insertColumn(myIndex);
        this->ui->table->setHorizontalHeaderItem(myIndex, new QTableWidgetItem("PKWIU"));
    } else {
        this->ui->table->removeColumn(myIndex);
    }
}

void MainWindow::toggleDiscountsColumn(bool value)
{
    int myIndex = 1;
    if(this->ui->table_pkwiu->isChecked()) {
        myIndex = 2;
    }
    if(value) {
        this->ui->table->insertColumn(myIndex);
        this->ui->table->setHorizontalHeaderItem(myIndex, new QTableWidgetItem("Rabat"));
    } else {
        this->ui->table->removeColumn(myIndex);
    }

}

void MainWindow::onGenerateButton()
{
    QString invoiceNr = getFormattedInvoiceNr();
    QString fileName = getFormattedFileName(invoiceNr);
    generateInvoicePDFToFile(fileName);
    incrementInvoiceNumberInSettings();
}

void MainWindow::onViewButton()
{
    removeTempFiles();
    QString fileName = getUniqueAppPDFFile();
    generateInvoicePDFToFile(fileName);
    QDesktopServices::openUrl(QUrl(fileName));

}

void MainWindow::on_actionGenerowanie_triggered()
{
    writeSettings();
}

void MainWindow::on_actionPodgl_d_triggered()
{
    onViewButton();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    removeTempFiles();
    if(ui->settings_autosave->isChecked()) {
        writeSettings();
    }
    event->accept();
}

void MainWindow::on_invoice_logoChooser_clicked()
{
    ui->invoice_logoPath->setText(QFileDialog::getOpenFileName(this, tr("Otwórz logo"), ".", tr("Obrazki (*.png *.jpg *.jpeg *.bmp")));
}

void MainWindow::on_invoice_resetToDefaults_clicked()
{
    this->ui->invoice_header->setPlainText(this->defaultHeader);
    this->ui->invoice_body->setPlainText(this->defaultBody);
    this->ui->invoice_footer->setPlainText(this->defaultFooter);
}

Ui::MainWindow *MainWindow::getUi()
{
    return ui;
}
