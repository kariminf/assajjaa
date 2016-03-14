#include "srchframe.h"
#include "ui_srchframe.h"

SrchFrame::SrchFrame(QWidget *parent) :
    FuncFrame(parent),
    ui(new Ui::SrchFrame)
{
    initialize();
    rq = new Requestor();
    rq->connect();
    html = new HTMLuncher();
    html->setLang(Language::getCurrentLanguage());
}

SrchFrame::~SrchFrame()
{
    rq->desconnect();
    delete ui;
}


void SrchFrame::initUI()
{
    ui->setupUi(this);
    QPalette palette;

    //hasContent = false;
    //Set the style od webkit page to transparent
    palette.setBrush(QPalette::Base, Qt::transparent);
    ui->srchPage->page()->setPalette(palette);
    ui->srchPage->setAttribute(Qt::WA_OpaquePaintEvent, false);
    ui->srchPage->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect( ui->srchPage, SIGNAL( linkClicked( QUrl ) ),
                      this, SLOT( linkClickedSlot( QUrl ) ) );
    //init the search components
    initBeginingFields();
    initRhymeFields();
    initWaznFields();

    changeStyle(Style::getCurrentStyle());
}


void SrchFrame::initExporter()
{

}

void SrchFrame::initExporter(Export exporter)
{

    /*
    exporter.setRTL(rtl);
    exporter.addContent("<p><h1>" + currentVerb + "</h1></p><hr>\n");
    exporter.addContent("<p><h3>" + ui->verbType->text() + "</h3></p>\n");
    if(Export::getConfigExportPart("standard")){
        exporter.addContent("<p><h2>" + ui->ConjgTab->tabText(0) + "</h2></p>\n");
        QString data = ui->standardConj->page()->mainFrame()->findFirstElement("body").firstChild().toOuterXml();
        exporter.addContent(data);
    }
    if(Export::getConfigExportPart("basic")){
        exporter.addContent("<p><h2>" + ui->ConjgTab->tabText(1) + "</h2></p>\n");
        QString data = ui->basicConj->page()->mainFrame()->findFirstElement("body").firstChild().toOuterXml();
        exporter.addContent(data);
    }
    if(Export::getConfigExportPart("complex")){
        exporter.addContent("<p><h2>" + ui->ConjgTab->tabText(2) + "</h2></p>\n");
        QString data = ui->complexConj->page()->mainFrame()->findFirstElement("body").firstChild().toOuterXml();
        exporter.addContent(data);
    }

    if(Export::getConfigExportPart("styled"))
        exporter.setStyle(QDir(QString(dataFolder) + "styles/" + stylesheet).absolutePath());
*/
}



/*!
 * \brief ConjFrame::doConj This function is used to show different conjugation forms
 *
 * This function search for the existance of the verb, using Edict2 module.
 * Then, it calls for:
 * - ConjFrame::basicConjugation To show the standard and basic conjugation forms.
 * - ConjFrame::complexConjugation To show the complex conjugation forms.
 */

void SrchFrame::doSearch()
{
    rq->clearRequest();

    html->clear();

    QString qafiya = ui->rhyme->text().trimmed();
    if (qafiya.length() < 1)
        return;

    rq->addQafiya(qafiya);

    switch (ui->tempMethod->currentIndex()) {
    case 1:{
        QString wazn = ui->tempChooser->currentText();
        rq->addWazn(wazn);
        break;
    }
    default:
        break;
    }


    switch (ui->beginMethod->currentIndex()) {
    case 1:{
        QString begin = ui->begining->text().trimmed();
        if (begin.length() < 1)
            break;
        rq->addBegining(begin);
        break;
    }
    default:
        break;
    }

    QStringList result = rq->getResult();

    qDebug() << result.size();
    foreach (QString word, result){
        //qDebug() << word;
        html->addWord(word);
    }

    html->finalize();
    ui->srchPage->setHtml(html->getHTML());
    //qDebug() << html->getHTML();
}



void SrchFrame::refreshLanguage(bool rtl)
{
    this->rtl = rtl;
    html->setLang(Language::getCurrentLanguage());
    ui->retranslateUi(this);

}



void SrchFrame::zoom(signed char sign)
{

    if (sign < 0){
        ui->srchPage->setTextSizeMultiplier(qMax(0.5, ui->srchPage->textSizeMultiplier() - 1.0 / 10.0));

        return;
    }

    if (sign > 0){
        ui->srchPage->setTextSizeMultiplier(qMin(2.5,ui->srchPage->textSizeMultiplier() + 1.0 / 10.0));
        return;
    }

    ui->srchPage->setTextSizeMultiplier(1.0);

}


void SrchFrame::changeStyle(QString styleID)
{
    stylesheet = styleID + ".css";
    setCSS(ui->srchPage, stylesheet);
}


void SrchFrame::initWaznFields()
{
    QFile wazns (QString(LingPath) + "awzan.txt");
    if (wazns.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream txtStream(&wazns);
        txtStream.setCodec("UTF-8");
        while(! txtStream.atEnd()){
            QString wazn = txtStream.readLine().trimmed();

            if (wazn.length() > 0)
                ui->tempChooser->addItem(wazn);
        }

        ui->tempChooser->setVisible(false);
    }
}

void SrchFrame::initRhymeFields()
{
    QFile qawafi (QString(LingPath) + "qawafi.txt");
    if (qawafi.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream txtStream(&qawafi);
        txtStream.setCodec("UTF-8");
        while(! txtStream.atEnd()){
            QString qafiya = txtStream.readLine().trimmed();

            if (qafiya.length() > 0)
                ui->rhymeChooser->addItem(qafiya);
        }
    }
    ui->rhymeChooser->setVisible(false);
}

void SrchFrame::initBeginingFields()
{
    ui->begining->setVisible(false);
}

void SrchFrame::on_rhymeMethod_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->rhymeChooser->setVisible(false);
        ui->rhyme->setVisible(true);
        break;
    case 1:
        ui->rhymeChooser->setVisible(true);
        ui->rhyme->setVisible(false);
        break;
    default:
        break;
    }
}

void SrchFrame::on_rhymeChooser_currentIndexChanged(const QString &text)
{
    ui->rhyme->setText(text);
}

void SrchFrame::on_tempMethod_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->tempChooser->setVisible(false);
        break;
    case 1:
        ui->tempChooser->setVisible(true);
        break;
    default:
        break;
    }
}

void SrchFrame::on_beginMethod_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->begining->setVisible(false);
        break;
    case 1:
        ui->begining->setVisible(true);
        break;
    default:
        break;
    }
}

void SrchFrame::on_search_clicked()
{
    doSearch();
}

void SrchFrame::linkClickedSlot(QUrl url)
{
    QDesktopServices::openUrl(url);
}
