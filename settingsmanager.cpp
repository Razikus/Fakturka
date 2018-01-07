#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
}

QVariant SettingsManager::getSetting(QString group, const QString &setting, const QVariant &def)
{
    settings->beginGroup(group);
    QVariant value = settings->value(setting, def);
    settings->endGroup();
    return value;
}

QString SettingsManager::getSettingString(QString group, const QString &setting, const QVariant &def)
{
    return getSetting(group, setting, def).toString();
}

bool SettingsManager::getSettingBool(QString group, const QString &setting, const QVariant &def)
{
    return getSetting(group, setting, def).toBool();
}

int SettingsManager::getSettingInt(QString group, const QString &setting, const QVariant &def)
{
    return getSetting(group, setting, def).toInt();
}

double SettingsManager::getSettingDouble(QString group, const QString &setting, const QVariant &def)
{
    return getSetting(group, setting, def).toDouble();
}

void SettingsManager::setSetting(QString group, const QString &setting, const QVariant &value)
{
    settings->beginGroup(group);
    settings->setValue(setting, value);
    settings->endGroup();
}
