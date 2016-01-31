#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T14:58:49
#
#-------------------------------------------------

QT       += core gui sql webkit network
CONFIG   += help
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
TARGET = Assajjaa
TEMPLATE = app
VERSION = 0.0.2 #dev version

DEFINES += VERSION=\\\"$$VERSION\\\"
DEFINES += arbDbPath=\\\"./DB/arwords.db\\\" #/usr/share/assajjaa/DB
DEFINES += LingPath=\\\"./Ling/\\\" #/usr/share/assajjaa/DB
DEFINES += transPath=\\\"./i18n/\\\" #/usr/share/assajjaa/DB


SOURCES +=  main.cpp\
            Ui/mainwindow.cpp \
            Ui/about.cpp \
            Ui/preference.cpp \
            Ui/help.cpp \
            Ui/helpviewer.cpp \
            Ui/srchframe.cpp \
            UiHelper/language.cpp \
            UiHelper/export.cpp \
            UiHelper/tray.cpp \
            UiHelper/style.cpp \
            UiHelper/funcframe.cpp \
            Data/requestor.cpp \
            Data/transformer.cpp \
    Data/htmluncher.cpp



HEADERS  += UiHelper/msg.h \
            Ui/mainwindow.h \
            Ui/mainwindow.h \
            Ui/about.h \
            Ui/preference.h \
            Ui/help.h \
            Ui/helpviewer.h \
            Ui/srchframe.h \
            UiHelper/language.h \
            UiHelper/export.h \
            UiHelper/tray.h \
            UiHelper/style.h \
            UiHelper/funcframe.h \
            Data/requestor.h \
            Data/transformer.h \
    Data/htmluncher.h

FORMS    += Ui/mainwindow.ui \
            Ui/about.ui \
            Ui/preference.ui \
            Ui/help.ui \
            Ui/srchframe.ui

TRANSLATIONS    +=  Media/i18n/ar.ts\
                    Media/i18n/ja.ts\
                    Media/i18n/fr.ts

RESOURCES += \
    Media/about.qrc \
    Media/icons.qrc \
    Media/output.qrc

#Used when packaging only
#DESTDIR = ../bin/release

win32:RC_FILE = jpconj.rc

unix {
system(mkdir ../bin)
system(mkdir ../bin/release)

system(cd Media/i18n; lrelease *.ts)
system(mkdir ../bin/release/i18n)
system(mv Media/i18n/*.qm ../bin/release/i18n)
system(cp Media/i18n/*.ini ../bin/release/i18n)
system(mkdir ../bin/release/DB)
system(cp Media/DB/* ../bin/release/DB)

system(mkdir ../bin/release/Ling)
system(cp Media/Ling/* ../bin/release/Ling)
}
