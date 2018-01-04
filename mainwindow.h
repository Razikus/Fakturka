#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
public slots:
    void addRowToTable();
    void removeRowFromTable();
    void togglePKWIUColumn(bool value);
    void toggleDiscountsColumn(bool value);
private slots:
    void on_actionGenerowanie_triggered();

private:
    Ui::MainWindow *ui;
    bool pkwiuChecked = false;
    bool discountsChecked = false;
};



#endif // MAINWINDOW_H
