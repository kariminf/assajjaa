#-------------------------------------------------
#
# Project created by QtCreator 2015-12-01T14:58:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assajjaa
TEMPLATE = app
VERSION = 0.0.1

DEFINES += arbDbPath=\\\"./DB/arwords.db\\\" #/usr/share/assajjaa/DB
DEFINES += LingPath=\\\"./Ling/\\\" #/usr/share/assajjaa/DB


SOURCES += main.cpp\
        mainwindow.cpp \
    Data/requestor.cpp \
    Data/transformer.cpp

HEADERS  += mainwindow.h \
    Data/requestor.h \
    Data/transformer.h

FORMS    += mainwindow.ui

TRANSLATIONS    +=  Media/i18n/ar.ts\
                    Media/i18n/ja.ts\
                    Media/i18n/fr.ts

#Used when packaging only
#DESTDIR = ../bin/release

unix {
system(mkdir ../bin)
system(mkdir ../bin/release)

system(cd Media/i18n; lrelease *.ts)
system(mkdir ../bin/release/i18n)
system(mv Media/i18n/*.qm ../bin/release/i18n)
system(mkdir ../bin/release/DB)
system(cp Media/DB/* ../bin/release/DB)

system(mkdir ../bin/release/Ling)
system(cp Media/Ling/* ../bin/release/Ling)
}
