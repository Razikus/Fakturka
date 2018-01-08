#include "invoicestockcreator.h"

InvoiceStockCreator::InvoiceStockCreator()
{
}

QString InvoiceStockCreator::createHTMLTag()
{
    HTMLTableCreator* creator = new HTMLTableCreator("stock");
    QString thClass = "stockTH";
    QString tdClass = "stockTD";

    int rows = this->table->rowCount();
    int columns = this->table->columnCount();


    creator->beginTr("stockHeaderRow");
    creator->th("stockHeader", "Lp");
    for(int column = 0; column < columns; column++) {
        creator->th("stockHeader", getNameOfColumn(column));
    }
    creator->closeTr();

    for(int row = 0; row < rows; row++) {
        creator->beginTr("stockItemRow");
        creator->td("stockCell", QString::number(row + 1));

        for(int column = 0; column < columns; column++) {
            creator->td("stockCell", valueOfRowAt(row, column));
        }
        creator->closeTr();
    }



    return creator->toString();
}

void InvoiceStockCreator::setContext(QTableWidget *table)
{
    this->table = table;
}

QString InvoiceStockCreator::getNameOfColumn(int column)
{
    if(column == -1) {
        return "LP";
    } else {
        return this->table->horizontalHeaderItem(column)->text();
    }
}

QString InvoiceStockCreator::valueOfRowAt(int row, int column)
{
    QTableWidgetItem* item =  this->table->item(row, column);
    if(item != nullptr) {
        return item->text();
    } else {
        return "";
    }
}
