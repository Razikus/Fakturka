#include "htmltablecreator.h"

HTMLTableCreator::HTMLTableCreator()
{
    this->tableBuffer = "<table>";

}

HTMLTableCreator::HTMLTableCreator(QString cssClass)
{
    this->tableBuffer = this->tableBuffer + "<table class=\"" + cssClass + "\">";
}

HTMLTableCreator *HTMLTableCreator::beginTr(QString cssClass)
{
    this->tableBuffer = this->tableBuffer + "<tr class=\"" + cssClass + "\">";
    return this;
}

HTMLTableCreator *HTMLTableCreator::closeTr()
{
    this->tableBuffer = this->tableBuffer + "</tr>";
    return this;
}

HTMLTableCreator *HTMLTableCreator::td(QString cssClass, QString value)
{
    this->tableBuffer = this->tableBuffer + "<td class=\"" + cssClass + "\">" + value + "</td>";
    return this;
}

HTMLTableCreator *HTMLTableCreator::th(QString cssClass, QString value)
{
    this->tableBuffer = this->tableBuffer + "<th class=\"" + cssClass + "\">" + value + "</th>";
    return this;
}

QString HTMLTableCreator::toString()
{
    return this->tableBuffer + "</table>";
}
