#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QSettings settings("ApproxTeam", "Fakturka");

    settings.beginGroup("Window");
    settings.setValue("size", size());
    settings.endGroup();

    settings.beginGroup("Seller");
    settings.setValue("name", ui->seller_name->text());
    settings.setValue("nip", ui->seller_nip->text());
    settings.setValue("account", ui->seller_account->text());
    settings.setValue("bank", ui->seller_bank->text());
    settings.setValue("street", ui->seller_street->text());
    settings.setValue("city", ui->seller_city->text());
    settings.endGroup();

}

void MainWindow::loadSettings()
{
    QSettings settings("ApproxTeam", "Fakturka");
    qDebug() << settings.fileName();

    settings.beginGroup("Window");
    resize(settings.value("size", QSize(1024, 780)).toSize());
    settings.endGroup();

    settings.beginGroup("Seller");
    ui->seller_name->setText(settings.value("name", "").toString());
    ui->seller_nip->setText(settings.value("nip", "").toString());
    ui->seller_account->setText(settings.value("account", "").toString());
    ui->seller_bank->setText(settings.value("bank", "").toString());
    ui->seller_street->setText(settings.value("street", "").toString());
    ui->seller_city->setText(settings.value("city", "").toString());
    settings.endGroup();

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

void MainWindow::on_actionGenerowanie_triggered()
{
    writeSettings();
}
