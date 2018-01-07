#ifndef INVOICESTOCKCREATOR_H
#define INVOICESTOCKCREATOR_H

#include "htmltablecreator.h"

#include <QTableWidget>
#include <QtWidgets>




class InvoiceStockCreator
{
public:
    InvoiceStockCreator();
    QString createHTMLTag();
    void setContext(QTableWidget* table);
private:
    QTableWidget *table;
    QString getNameOfColumn(int column);
    QString valueOfRowAt(int row, int column);
};


#endif // INVOICESTOCKCREATOR_H
