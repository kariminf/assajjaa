#ifndef HTMLUNCHER_H
#define HTMLUNCHER_H

#include <qstring.h>
#include <qfile.h>
#include <QTextStream>

class HTMLuncher
{
public:
    HTMLuncher();
    QString readHtmlFile(QString URL);
    void addWord(QString word);
    void finalize();
    void clear();
    void setLang(QString lang);
    QString getHTML();

private:
    QString content;
    QString lang;

    QString foundWordHTML;
    void loadFoundWord();

    QString searchEngines;
    void loadSearchEngines();

};

#endif // HTMLUNCHER_H
