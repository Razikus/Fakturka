#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T19:34:28
#
#-------------------------------------------------

QT       += core gui
QT += printsupport
QT += webenginewidgets webengine


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fakturka
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    settingsmanager.cpp \
    formatter.cpp \
    invoicestockcreator.cpp \
    htmltablecreator.cpp

HEADERS += \
        mainwindow.h \
    settingsmanager.h \
    formatter.h \
    invoicestockcreator.h \
    htmltablecreator.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    res/resources.qrc

SMTP_LIBRARY_LOCATION = /home/edge/build-SMTPEmail-Desktop_Qt_5_10_0_GCC_64bit-Release

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION

