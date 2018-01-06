#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QSettings>
#include <QString>



class SettingsManager
{
public:
    SettingsManager();
    QVariant getSetting(QString group, const QString &setting, const QVariant &def = QVariant());
    QString getSettingString(QString group, const QString &setting, const QVariant &def = QString());
    bool getSettingBool(QString group, const QString &setting, const QVariant &def = QString());
    int getSettingInt(QString group, const QString &setting, const QVariant &def = QString());

    void setSetting(QString group, const QString &setting, const QVariant &value);

private:
    QSettings* settings = new QSettings("ApproxTeam", "Fakturka");
};



#endif // SETTINGSMANAGER_H
