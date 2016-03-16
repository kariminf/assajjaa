#include "htmluncher.h"

HTMLuncher::HTMLuncher()
{
    clear();
    loadFoundWord();
    loadSearchEngines();
    this->lang = "en";

}

void HTMLuncher::setLang(QString lang){
    this->lang = lang;
}

QString HTMLuncher::getHTML()
{
    return content;
}


/*!
 * \brief jpconjmain::readHtmlFile Reads an HTML file and return a QString
 * \param URL URL of the HTML file, we want to read.
 * \return A QString which is the content of this HTML file.
 */
QString HTMLuncher::readHtmlFile(QString URL)
{
    QString result="";
    QFile HtmlFile(URL);

    if (HtmlFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream htmlStream(&HtmlFile);
        result = htmlStream.readAll();
    }

    return result;
}

void HTMLuncher::addWord(QString word)
{
    QString linksHTML = searchEngines;
    linksHTML.replace("@word", word);
    linksHTML.replace("@lang", lang);

    QString wordHTML = foundWordHTML;
    wordHTML.replace("@word", word);
    wordHTML.replace("@links", linksHTML);

    content += wordHTML + "\n";
}

void HTMLuncher::finalize()
{
    content += "</table>\n";
    content += "</body>\n";
    content += "</html>\n";
}



void HTMLuncher::clear()
{
    content = "<!doctype html>\n";
    content += "<html>\n";
    content += "<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\" />\n";
    content += "<style>\n";
    content += "*{font-family:" + Style::getCurrentFont(false) + ";";
    content += "font-size:" + QString::number(Style::getCurrentFontSize()) + "pt;}";
    content += ".word{font-family:" + Style::getCurrentFont(true) + ";}";
    content += "\n</style>\n";
    content += "<body>\n";
    content += "<table id=\"_SrchTable\">\n";
}


void HTMLuncher::loadFoundWord()
{
    foundWordHTML = readHtmlFile(":/output/foundWord");
}

void HTMLuncher::loadSearchEngines()
{
    searchEngines = readHtmlFile(":/output/searchEngines");
}

