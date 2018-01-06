#include "formatter.h"

Formatter::Formatter(QString toFormat)
{
    this->toFormat = toFormat;
}

Formatter* Formatter::format(QString tag, int format)
{
    this->toFormat.replace(tag, QString::number(format));
    return this;
}


Formatter* Formatter::format(QString tag, QString format)
{
    this->toFormat.replace(tag, format);
    return this;
}

QString Formatter::toString()
{
    return this->toFormat;
}
