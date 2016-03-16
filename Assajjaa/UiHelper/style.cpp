#include "style.h"

/*!
 * \class Style
 * This class is used to manage the tables styles (CSS)
 */

QHash<QString, Styleinfo*> Style::styles;
QString Style::currentstyle = "";
QString Style::currentFont = "";
QString Style::currentArFont = "";
int Style::currentFontSize = 14;
Style* Style::_instance = new Style();


/*******************************************************
 *                    PUBLIC
 *******************************************************/

Styleinfo::Styleinfo()
{

}


Style::Style()
{

}

void Style::signalStyleChanged(QString styleID)
{
    emit styleChanged(styleID);
}

void Style::signalFontChanged(QString font, QString arfont, int size)
{
    emit fontChanged(font, arfont, size);
}

void Style::loadStyles()
{
    /*
    styles.clear();

    QDir styleDefaultDir (QString(dataFolder) + "styles/");
    QStringList styleFiles = styleDefaultDir.entryList(QStringList("*.ini"));

    foreach (QString styleFile, styleFiles){
        QString styleFileName = styleFile;
        styleFileName.chop(4);
        Styleinfo* styleinfo = new Styleinfo();

        QSettings styleSettings(QString(dataFolder) + "styles/" + styleFile, QSettings::IniFormat);
        styleSettings.setIniCodec("UTF-8");
        styleinfo->name = styleSettings.value("name").toString();
        styleinfo->author = styleSettings.value("author").toString();
        styleinfo->date = styleSettings.value("date").toString();
        styleinfo->desc = styleSettings.value("desc").toString();

        styles.insert(styleFileName, styleinfo);

    }

    setStyle();
    */
}

/*!
 * \brief Style::getStyleInfo Get ID's and names of available style sheets.
 * \return A QHash of style-ID as key, and style-name as value. \n
 * Example: <DzStyle, DzCoding default style>, etc.
 */
QHash<QString, Styleinfo*> Style::getStyleInfo()
{
    return styles;
}


void Style::setConfigStyle(QString styleID)
{
    QSettings settings;
    settings.setValue("style", styleID);
}


QString Style::getConfigStyle()
{
    QSettings settings;

    return settings.value("style", "??").toString();
}


QString Style::getCurrentStyle()
{
    return currentstyle;
}


void Style::addStyleReceiver(const QObject * receiver, const char * receiverSlot)
{
    connect(_instance, SIGNAL(styleChanged(QString)), receiver, receiverSlot);
}

void Style::addFontReceiver(const QObject *receiver, const char *receiverSlot)
{
    connect(_instance, SIGNAL(fontChanged(QString, QString, int)), receiver, receiverSlot);
}

QString Style::getConfigFont(bool arabic)
{
    QSettings settings;

    if (arabic)
        return settings.value("ar_font-family", "").toString();
    return settings.value("font-family", "").toString();
}

QString Style::getCurrentFont(bool arabic)
{
    if (arabic)
        return currentArFont;

    return currentFont;
}

void Style::setConfigFont(QString font, bool arabic)
{
    QSettings settings;

    if (arabic)
        settings.setValue("ar_font-family", font);
    else
        settings.setValue("font-family", font);
}

int Style::getConfigFontSize()
{
    QSettings settings;

    return settings.value("font-size", "14").toInt();
}

int Style::getCurrentFontSize()
{
    return currentFontSize;
}

void Style::setConfigFontSize(int fontSize)
{
    QSettings settings;
    settings.setValue("font-size", fontSize);
}

/*
QStringList Style::getAvailableArabicFonts()
{
    QFontDatabase fontDB;
    return fontDB.families(QFontDatabase::Arabic);
}

QStringList Style::getAvailableFonts()
{
    QFontDatabase fontDB;
    return fontDB.families();
}*/


/*******************************************************
 *                   PUBLIC SLOTS
 *******************************************************/

void Style::setStyle()
{
    //currentstyle = styleID;
    QString styleID = getConfigStyle();
    if(!styles.contains(styleID)){
        styleID = "DzStyle";
        setConfigStyle(styleID);
    }

    if (styleID != currentstyle){
        currentstyle = styleID;
        _instance->signalStyleChanged(styleID);
        //qDebug() << "emit signal";
    }

}

void Style::setFont()
{
    QString font = getConfigFont(false);
    QString arfont = getConfigFont(true);
    int size = getConfigFontSize();
    bool changed = false;

    if (font != currentFont){
        currentFont = font;
        changed = true;
    }
    if (arfont != currentArFont){
        currentArFont = arfont;
        changed = true;
    }

    //qDebug() << "size:" << size << "current size" << currentFontSize;
    if (size != currentFontSize){
        currentFontSize = size;
        changed = true;
    }

    if (changed)
        _instance->signalFontChanged(font, arfont, size);

}
