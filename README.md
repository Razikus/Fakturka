1. Build testowany z wersją Qt5.1.10 i systemami - Windows 10 i Linux.
Kompilator dla windows - MSVC2017_64bit

Uruchom skrypt pullDependencies.sh

W QtCreator otwórz projekt Fakturka i libs/smtpclient

Skompiluj SmtpClient

Dodaj external library w projekcie Fakturka wskazujący na .lib ze skompilowanego smtpClient

Skompiluj Fakturka
