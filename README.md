# Build
Build testowany z wersją Qt5.1.10 i systemami - Windows 10 i Linux.
Kompilator dla windows - MSVC2017_64bit

Uruchom skrypt pullDependencies.sh

W QtCreator otwórz projekt Fakturka i projekt z folderu src/libs/smtpclient

Skompiluj SmtpClient

Dodaj external library w projekcie Fakturka wskazujący na .lib ze skompilowanego smtpClient

Skompiluj Fakturka


# Wymagania
## Windows
Do wysyłania maili przez protokół SSL lub TLS potrzebujemy OpenSSL w wersji 1_0_2j
Win64 https://cyberside.net.ee/security/Win64OpenSSL-1_0_2j.exe
Win32 https://cyberside.net.ee/security/Win32OpenSSL-1_0_2j.exe

Do budowania projektu nie można użyć kompilatora MinGW (QtWebEngine nie jest obsługiwany)


## Linux
Prawdopodobnie brak