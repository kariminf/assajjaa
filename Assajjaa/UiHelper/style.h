#ifndef STYLE_H
#define STYLE_H

#include <QCustomEvent>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QHash>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
//#include <QFontDatabase>

class Styleinfo
{
public:
    Styleinfo();
    QString name;
    QString author;
    QString date;
    QString desc;
};


class Style : public QObject
{
    Q_OBJECT

public:
    Style();
    void signalStyleChanged(QString styleID);
    void signalFontChanged(QString font, QString arfont, int size);

    static void loadStyles();
    static QHash<QString, Styleinfo *> getStyleInfo();
    static void setStyle();
    static void setFont();
    static QString getConfigStyle();
    static QString getCurrentStyle();
    static void setConfigStyle(QString styleID);
    static void addStyleReceiver(const QObject * receiver, const char * receiverSlot);
    static void addFontReceiver(const QObject * receiver, const char * receiverSlot);
    static QString getConfigFont(bool arabic);
    static QString getCurrentFont(bool arabic);
    static void setConfigFont(QString font, bool arabic);
    static int getConfigFontSize();
    static int getCurrentFontSize();
    static void setConfigFontSize(int fontSize);

    //static QStringList getAvailableArabicFonts();
    //static QStringList getAvailableFonts();

private:
    static QHash<QString, Styleinfo*> styles;
    static QString currentstyle;
    static QString currentFont;
    static QString currentArFont;
    static int currentFontSize;
    //static Style* getInstance();
    static Style* _instance;


signals:
    void styleChanged(QString styleID);
    void fontChanged(QString font, QString arfont, int size);
};

#endif // STYLE_H
