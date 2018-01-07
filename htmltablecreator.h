#ifndef HTMLTABLECREATOR_H
#define HTMLTABLECREATOR_H

#include <QString>



class HTMLTableCreator
{
public:
    HTMLTableCreator();
    HTMLTableCreator(QString cssClass);
    HTMLTableCreator* beginTr(QString cssClass);
    HTMLTableCreator* closeTr();
    HTMLTableCreator* td(QString cssClass, QString value);
    HTMLTableCreator* th(QString cssClass, QString value);

    QString toString();

private:
    QString tableBuffer;
};

#endif // HTMLTABLECREATOR_H
