#ifndef FORMATTER_H
#define FORMATTER_H

#include "mainwindow.h"
#include <QSettings>
#include <QtWidgets>
#include <QMainWindow>
#include <QPrinter>
#include <QString>



class Formatter
{
public:
    Formatter(QString toFormat);

    Formatter* format(QString tag, QString format);
    Formatter* format(QString tag, int format);

    QString toString();

private:
    QString toFormat;
};

#endif // FORMATTER_H
