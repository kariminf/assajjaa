#ifndef SRCHFRAME_H
#define SRCHFRAME_H

#include "UiHelper/export.h"
#include "UiHelper/msg.h"
#include "UiHelper/funcframe.h"
#include "Ui/preference.h"
#include <QWebElement>
#include <QWebFrame>


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
    void doSearch();
    virtual void zoom(signed char sign);
    virtual void refreshLanguage(bool rtl);
    virtual void changeStyle(QString styleID);


protected:
    virtual void initUI();
    virtual void initExporter();
    
private slots:
    void on_conjugateButton_clicked();
    void on_inputConjVerb_returnPressed();

private:
    Ui::SrchFrame *ui;


    //bool languageChanged;
    QString currentVerb;

    //void basicConjugation(QString verb, EdictType type);
    //void complexConjugation(QString verb, EdictType type);

    QString readHtmlFile(QString URL);
};

#endif // SRCHFRAME_H
