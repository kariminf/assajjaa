#ifndef SRCHFRAME_H
#define SRCHFRAME_H

#include "UiHelper/export.h"
#include "UiHelper/msg.h"
#include "UiHelper/funcframe.h"
#include "Ui/preference.h"
#include "Data/requestor.h"
#include "Data/htmluncher.h"
#include <QWebElement>
#include <QWebFrame>
#include <QDesktopServices>


namespace Ui {
class SrchFrame;
}

class SrchFrame : public FuncFrame
{
    Q_OBJECT
    
public:
    explicit SrchFrame(QWidget *parent = 0);
    ~SrchFrame();

    void initExporter(Export exporter);
    virtual void zoom(signed char sign);
    virtual void refreshLanguage(bool rtl);
    virtual void changeStyle(QString styleID);
    virtual void changeFont(QString font, QString arfont, int size);


protected:
    virtual void initUI();
    virtual void initExporter();
    
private slots:
    void on_rhymeMethod_currentIndexChanged(int index);
    void on_rhymeChooser_currentIndexChanged(const QString &text);

    void on_tempMethod_currentIndexChanged(int index);

    void on_beginMethod_currentIndexChanged(int index);

    void on_search_clicked();

    void linkClickedSlot(QUrl url);

private:
    Ui::SrchFrame *ui;
    Requestor *rq;
    HTMLuncher *html;

    //bool languageChanged;
    QString currentVerb;

    void initWaznFields();
    void initRhymeFields();
    void initBeginingFields();
    void doSearch();

};

#endif // SRCHFRAME_H
