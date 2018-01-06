#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingsmanager.h"

#include <QSettings>
#include <QtWidgets>
#include <QMainWindow>
#include <QPrinter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDatesToToday();
    void setInvoiceNumberToCorresponding();

    void writeSettings();
    void loadSettings();

    void closeEvent(QCloseEvent* event);
    enum AppArea {
        SELLER,
        BUYER,
        INVOICE,
        TABLE,
        GENERATOR,
        SETTINGS
    };
    Q_ENUM(AppArea);

    Ui::MainWindow *getUi();

public slots:
    void addRowToTable();
    void removeRowFromTable();
    void togglePKWIUColumn(bool value);
    void toggleDiscountsColumn(bool value);
    void onGenerateButton();
    void onViewButton();

private slots:
    void on_actionGenerowanie_triggered();


    void on_actionPodgl_d_triggered();

    void on_invoice_logoChooser_clicked();

    void on_invoice_resetToDefaults_clicked();

private:
    Ui::MainWindow *ui;
    bool pkwiuChecked = false;
    bool discountsChecked = false;
    SettingsManager settingsManager;


    void writeWindowSettings();
    void writeSellerSettings();
    void writeBuyerSettings();
    void writeInvoiceSettings();
    void writeTableSettings();
    void writeGeneratorSettings();
    void writeApplicationSettings();

    void loadWindowSettings();
    void loadSellerSettings();
    void loadBuyerSettings();
    void loadInvoiceSettings();
    void loadTableSettings();
    void loadGeneratorSettings();
    void loadApplicationSettings();

    void incrementInvoiceNumberInSettings();

    void generateInvoicePDFToFile(QString fileName);

    void removeTempFiles();

    QString getFormattedInvoiceNr();
    QString getFormattedFileName(QString invoiceNr);

    QString getCurrentNameOfInvoiceNumber();

    QString getUniqueName();
    QString getUniqueAppTempFile();
    QString getUniqueAppPDFFile();

    QString defaultHeader;
    QString defaultBody;
    QString defaultFooter;

    QString getFormattedDocHTML();

    QString formatStringWithAvalaibleTags(QString);
};

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString::fromStdString(std::string(QMetaEnum::fromType<QEnum>().valueToKey(value)));
}



#endif // MAINWINDOW_H
