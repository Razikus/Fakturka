#include "formatter.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIODevice>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    invoiceStockCreator()
{
    this->settingsManager = SettingsManager();
    ui = new Ui::MainWindow;
    ui->setupUi(this);


    this->defaultHeader = ui->invoice_header->toPlainText();
    this->defaultBody = ui->invoice_body->toPlainText();
    this->defaultFooter = ui->invoice_footer->toPlainText();


    this->setDatesToToday();
    this->setInvoiceNumberToCorresponding();
    this->loadSettings();
    this->invoiceStockCreator.setContext(this->ui->table);


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
    settingsManager.setSetting(settingName, "margup", ui->invoice_margup->value());
    settingsManager.setSetting(settingName, "margdown", ui->invoice_margdown->value());
    settingsManager.setSetting(settingName, "margright", ui->invoice_margright->value());
    settingsManager.setSetting(settingName, "margleft", ui->invoice_margleft->value());

    QString format = "A4";
    if(ui->invoice_a5format->isChecked()) {
        format = "A5";
    }
    settingsManager.setSetting(settingName, "format", format);

}

void MainWindow::writeTableSettings()
{
    QString settingName = QtEnumToString(AppArea::TABLE);
    settingsManager.setSetting(settingName, "pkwiu", ui->table_pkwiu->isChecked());
    settingsManager.setSetting(settingName, "discount", ui->table_discount->isChecked());
    settingsManager.setSetting(settingName, "autoCalculate", ui->table_autoCalculate->isChecked());

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
    ui->invoice_margup->setValue(settingsManager.getSettingDouble(settingName, "margup"));
    ui->invoice_margdown->setValue(settingsManager.getSettingDouble(settingName, "margdown"));
    ui->invoice_margright->setValue(settingsManager.getSettingDouble(settingName, "margright"));
    ui->invoice_margleft->setValue(settingsManager.getSettingDouble(settingName, "margleft"));

    QString format = settingsManager.getSettingString(settingName, "format");
    if(format == "A5") {
        ui->invoice_a5format->setChecked(true);
    } else {
        ui->invoice_a4format->setChecked(true);
    }
}



void MainWindow::loadTableSettings()
{
    QString settingName = QtEnumToString(AppArea::TABLE);
    ui->table_pkwiu->setChecked(settingsManager.getSettingBool(settingName, "pkwiu", QVariant(false)));
    ui->table_discount->setChecked(settingsManager.getSettingBool(settingName, "discount", QVariant(false)));
    ui->table_autoCalculate->setChecked(settingsManager.getSettingBool(settingName, "autoCalculate", QVariant(false)));

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
    double left = ui->invoice_margleft->value();
    double right = ui->invoice_margright->value();
    double bottom = ui->invoice_margdown->value();
    double top = ui->invoice_margup->value();
    QPageSize::PageSizeId pagesize = QPageSize::A4;
    if(ui->invoice_a5format->isChecked()) {
        pagesize = QPageSize::A5;
    }
    QPageLayout layout = QPageLayout(QPageSize(pagesize), QPageLayout::Orientation::Portrait, QMarginsF(left, top, right, bottom));
    this->printToPDF(html, fileName, layout);
}

void MainWindow::printToPDF(QString html, QString fileName, QPageLayout layout)
{
    QtWebEngine::initialize();
    QWebEnginePage page;
    QEventLoop loop;
    loop.connect(&page, &QWebEnginePage::loadFinished, [&page, &loop, &fileName, &layout]() {
        page.printToPdf([&loop, &fileName] (QByteArray ba) {
            QFile f(fileName);
            if (f.open(QIODevice::WriteOnly))
            {
                f.write(ba);
                f.close();
            } else {
                qDebug() << "Error opening file for writing" << fileName << f.errorString();
            }
            loop.exit();
        }, layout );
    });
    page.setHtml(html, QUrl("file://"));
    loop.exec();
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
    return formatStringWithAvalaibleTags(currentFormat);

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

    QString currentYear = QDate::currentDate().toString("yyyy");
    QString currentMonth = QDate::currentDate().toString("MM");
    QString currentDay = QDate::currentDate().toString("DD");


    formatter->format("%yyyy%", currentYear);
    formatter->format("%MM%", currentMonth);
    formatter->format("%dd%", currentDay);
    QString settingName = QtEnumToString(AppArea::INVOICE);
    int currentMonthInvoiceNr = settingsManager.getSettingInt(settingName + "/NUMBER", getCurrentNameOfInvoiceNumber(), 1);
    formatter->format("%NR%", currentMonthInvoiceNr);

    if(formatter->contains("%")) {
        formatter->format("%NRFAKTURY%", getFormattedInvoiceNr());
        formatter->format("%LOGO%", ui->invoice_logoPath->text());
        formatter->format("%DATAWYSTAWIENIA%", ui->invoice_issued->text());
        formatter->format("%DATASPRZEDAZY%", ui->invoice_selldate->text());
        formatter->format("%TERMINPLATNOSCI%", ui->invoice_term->text());
        formatter->format("%TYPPLATNOSCI%", ui->invoice_paymenttype->text());

        formatter->format("%SPRZEDAJACYNAZWA%", ui->seller_name->text());
        formatter->format("%SPRZEDAJACYULICA%", ui->seller_street->text());
        formatter->format("%SPRZEDAJACYKODPOCZTOWYMIASTO%", ui->seller_city->text());
        formatter->format("%SPRZEDAJACYNIP%", ui->seller_nip->text());
        formatter->format("%SPRZEDAJACYBANK%", ui->seller_bank->text());
        formatter->format("%SPRZEDAJACYKONTO%", ui->seller_account->text());

        formatter->format("%KUPUJACYNAZWA%", ui->buyer_name->text());
        formatter->format("%KUPUJACYULICA%", ui->buyer_street->text());
        formatter->format("%KUPUJACYKODPOCZTOWYMIATO%", ui->buyer_city->text());
        formatter->format("%KUPUJACYNIP%", ui->buyer_nip->text());

        formatter->format("%TOWARWARTOSCNETTO%", getSumOfNetto());
        formatter->format("%TOWARWARTOSCVAT%", getSumOfVat());
        formatter->format("%TOWARWARTOSCBRUTTO%", getSumOfBrutto());
        formatter->format("%TOWARWARTOSCNETTOPORABACIE%", getSumOfNettoAfterDiscounts());

        formatter->format("%TOWAR%", this->invoiceStockCreator.createHTMLTag());
    }
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
    int afterDiscounts = 5;
    if(this->ui->table_pkwiu->isChecked()) {
        myIndex = 2;
        afterDiscounts = 6;
    }
    if(value) {
        this->ui->table->insertColumn(myIndex);
        this->ui->table->setHorizontalHeaderItem(myIndex, new QTableWidgetItem("Rabat %"));
        this->ui->table->insertColumn(afterDiscounts);
        this->ui->table->setHorizontalHeaderItem(afterDiscounts, new QTableWidgetItem("Cena netto po rabacie"));
        this->ui->table->setColumnWidth(afterDiscounts, 200);
    } else {
        this->ui->table->removeColumn(myIndex);
        this->ui->table->removeColumn(afterDiscounts - 1);
    }

    on_actionCalculate_triggered();

}

void MainWindow::onGenerateButton()
{
    QString fileName = formatStringWithAvalaibleTags(ui->generator_filename->text());
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

void MainWindow::on_actionGenerate_triggered()
{
    writeSettings();
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
    this->invoiceStockCreator.createHTMLTag();
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


void MainWindow::on_table_cellChanged(int row, int column)
{
    int nettoColumn = this->ui->table->columnCount() - 4;
    int vatColumn = this->ui->table->columnCount() - 3;
    int afterDiscountsColumn = 5;
    int discountsColumn = 1;
    if(this->ui->table_pkwiu->isChecked()) {
        discountsColumn = 2;
        afterDiscountsColumn = 6;
    }

    if(this->ui->table_discount->isChecked()) {
        nettoColumn = nettoColumn - 1;
    }

    if(ui->table_discount->isChecked() && ui->table_autoCalculate->isChecked() && (column == discountsColumn || column == nettoColumn)) {

        calculateDiscountsForRow(row);
        calculateBruttoForRow(row);
    }
    if(ui->table_autoCalculate->isChecked() && (column == nettoColumn || column == vatColumn)) {
        calculateBruttoForRow(row);
    }

}


void MainWindow::calculateBruttoForRow(int row)
{
    int nettoColumn = this->ui->table->columnCount() - 4;
    int vatColumn = this->ui->table->columnCount() - 3;
    int vatAfterColumn = this->ui->table->columnCount() - 2;
    int bruttoAfterColumn = this->ui->table->columnCount() - 1;



    if(this->ui->table->item(row, nettoColumn) != nullptr && this->ui->table->item(row, vatColumn) != nullptr) {
        bool conversion;
        double netto = this->ui->table->item(row, nettoColumn)->text().replace(",", ".").toDouble(&conversion);
        if(!conversion) {
            return;
        }
        QString vatString = this->ui->table->item(row, vatColumn)->text();
        vatString = vatString.replace(",", ".");
        double vat = vatString.toDouble(&conversion);
        if(!conversion && vatString.contains("%")) {
            vatString = vatString.replace("%", "");
            vat = vatString.toDouble(&conversion);
            if(!conversion) {
                return;
            }
        }

        vat = vat / 100.0;

        double vatAfter = netto * vat;
        double bruttoAfter = netto + vatAfter;

        this->ui->table->setItem(row, vatAfterColumn, new QTableWidgetItem(QString::number(vatAfter, 'f', 2)));
        this->ui->table->setItem(row, bruttoAfterColumn, new QTableWidgetItem(QString::number(bruttoAfter, 'f', 2)));
    }


}

void MainWindow::calculateDiscountsForRow(int row)
{
    int nettoColumn = this->ui->table->columnCount() - 4;
    int afterDiscountsColumn = 5;
    int discountsColumn = 1;
    if(this->ui->table_pkwiu->isChecked()) {
        discountsColumn = 2;
        afterDiscountsColumn = 6;
    }


    if(this->ui->table_discount->isChecked()) {
        nettoColumn = nettoColumn - 1;
    }

    if(this->ui->table->item(row, nettoColumn) != nullptr && this->ui->table->item(row, discountsColumn) != nullptr) {
        bool conversion;
        double netto = this->ui->table->item(row, nettoColumn)->text().replace(",", ".").toDouble(&conversion);
        if(!conversion) {
            return;
        }
        QString discountsString = this->ui->table->item(row, discountsColumn)->text();
        discountsString = discountsString.replace(",", ".");
        double discounts = discountsString.toDouble(&conversion);
        if(!conversion && discountsString.contains("%")) {
            discountsString = discountsString.replace("%", "");
            discounts = discountsString.toDouble(&conversion);
            if(!conversion) {
                return;
            }
        }

        discounts = discounts / 100.0;

        double discountsAfter = netto * discounts;
        discountsAfter = netto - discountsAfter;

        this->ui->table->setItem(row, afterDiscountsColumn, new QTableWidgetItem(QString::number(discountsAfter, 'f', 2)));
    }



}

double MainWindow::getSumOfNetto()
{

    int nettoColumn = this->ui->table->columnCount() - 4;
    if(this->ui->table_discount->isChecked()) {
        nettoColumn--;
    }

    return getSumOfColumn(nettoColumn);
}

double MainWindow::getSumOfNettoAfterDiscounts()
{
    int afterDiscountsColumn = 5;
    if(this->ui->table_pkwiu->isChecked()) {
        afterDiscountsColumn = 6;
    }

    return getSumOfColumn(afterDiscountsColumn);

}

double MainWindow::getSumOfVat()
{
    int vatAfterColumn = this->ui->table->columnCount() - 2;

    return getSumOfColumn(vatAfterColumn);

}

double MainWindow::getSumOfBrutto()
{
    int bruttoAfterColumn = this->ui->table->columnCount() - 1;
    return getSumOfColumn(bruttoAfterColumn);

}

double MainWindow::getSumOfColumn(int columnToSum)
{
    int rows = this->ui->table->rowCount();

    double sum = 0.0;

    for(int row = 0; row < rows; row++) {

        if(this->ui->table->item(row, columnToSum) != nullptr) {
            bool conversion;
            QString itemString = this->ui->table->item(row, columnToSum)->text().replace(",", ".").replace("%", "");
            sum = sum + itemString.toDouble(&conversion);

            if(!conversion) {
                this->ui->table->item(row, columnToSum)->setTextColor(QColor("red"));
            }
        }
    }

    return sum;

}


void MainWindow::on_actionCalculate_triggered()
{
    int rows = this->ui->table->rowCount();

    for(int row = 0; row < rows; row++) {
        calculateDiscountsForRow(row);
        calculateBruttoForRow(row);
    }
}

void MainWindow::on_actionAddCargo_triggered()
{
    this->ui->table->insertRow(this->ui->table->rowCount());
}


void MainWindow::on_actionView_triggered()
{
    onViewButton();
}


