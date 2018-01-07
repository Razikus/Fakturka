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

Formatter* Formatter::format(QString tag, double format)
{
    this->toFormat.replace(tag, QString::number(format, 'f', 2));
    return this;
}

bool Formatter::contains(QString key)
{
    return this->toFormat.contains(key);
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
