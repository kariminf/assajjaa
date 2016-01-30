/*
    This file is part of JapKatsuyou project; an application that provide
    Japanese verb conjugation

    Copyright (C) 2013  Abdelkrime Aries <kariminfo0@gmail.com>
    Copyright (C) 2013  DzCoding group (JapKatsuyou team)

    Authors:
            Abdelkrime Aries <kariminfo0@gmail.com>
            Zakaria Smahi <zakaria08esi@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*!
 * \class jpconjmain
 * This class is used to manage the main window of the application.
 */


/*******************************************************
 *                    PUBLIC
 *******************************************************/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    doInit();
}



MainWindow::~MainWindow()
{
    delete ui;
}



/*******************************************************
 *                    PRIVATE
 *******************************************************/

/*!
 * \brief jpconjmain::doInit Initialize the components of the main window
 *
 * This function sets the language and direction of the main window.
 * You can call it in the constructor of this window.
 */
void MainWindow::doInit()
{

    workfrm = new SrchFrame(this);
    ui->formLayout->addWidget(workfrm);
    hasContent = false;
    languageChanged = true;
    currentVerb = "";

    //qDebug()<< QString(VERSION);
    Language::loadTranslations();
    bool rtl = Language::mainWindowDirection(this);

    ui->menu_View->addAction(ui->mainTool->toggleViewAction());
    ui->menu_View->addAction(ui->zoomTool->toggleViewAction());
    //ui->menu_View->addAction(ui->search->toggleViewAction());
    //ui->showt->setLayoutDirection(Qt::LeftToRight);

    //changeStyle(Style::getCurrentStyle());
    Style::addReceiver(this, SLOT(changeStyle(QString)));
    Style::loadStyles();
    //connect(style, SIGNAL(styleChanged(QString)), this, SLOT(changeStyle(QString)));


    //tray Icon
    trayIconSys = new JpconjTray(this);

    actionShow = new QAction(tr("Show"), this); //qApp->translate, "jpconjmain"
    actionShow->setIcon(QIcon(":/img/show.png"));

    connect(actionShow, SIGNAL(triggered()), trayIconSys, SLOT(showMain()) );
    trayIconSys->addAction(actionShow);
    trayIconSys->addSeparator();
}






/*!
 * \brief jpconjmain::openAbout This function is used to call "about" dialog box.
 */
void MainWindow::openAbout()
{
    winAbout = new About(this);
    winAbout->setLayoutDirection(this->layoutDirection());
    winAbout->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    winAbout->show();

}



/*!
 * \brief jpconjmain::openPref This function is used to call "preferences" dialog box.
 */
void MainWindow::openPref()
{
    winPref = new Preference(this);
    winPref->setLayoutDirection(this->layoutDirection());
    winPref->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    winPref->show();
}





/*!
 * \brief jpconjmain::doConj Used to export the result content as pdf, odt, etc.
 */
void MainWindow::doExport()
{
/*
    QHash<QString, QString> extensions = Msg::getExportExtensions();

    QStringList filters;

    foreach (QString extension, extensions.keys())
        filters << extensions.value(extension) + " (*" + extension + ")";

    QFileDialog saveDialog;
    saveDialog.setOptions(QFileDialog::DontUseNativeDialog | QFileDialog::DontConfirmOverwrite);  // with or without this
    saveDialog.setFilters(filters);
    //saveDialog.setDefaultSuffix("pdf");
    saveDialog.setFileMode(QFileDialog::AnyFile);
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setDirectory(QDir::homePath());
    QString defaultName = currentVerb + "_" + Language::getCurrentLanguage();
    saveDialog.selectFile(defaultName);

    int response = saveDialog.exec();
    if (response != QDialog::Accepted)
        return;

    QString filename = saveDialog.selectedFiles().first();

    if(!QString(".pdf|.odt|.htm").contains(filename.right(4))){
        QString selectedExtension = saveDialog.selectedNameFilter().right(5);
        selectedExtension.chop(1);
        filename += selectedExtension;
    }

    if(QFileInfo(filename).exists()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, Msg::fileExists(true), Msg::fileExists(false),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
    }

    Export exporter = initExporter();

    if (filename.endsWith(".pdf")){
        //exporter.exportPdf(filename);
        exporter.exportPdf(filename);
        return;
    }

    if (filename.endsWith(".odt")){
        exporter.exportOdf(filename);
        return;
    }

    if (filename.endsWith(".htm")){
        exporter.exportHtml(filename);
    }*/
}



void MainWindow::doPrint()
{
    /*QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    //dialog->setWindowTitle(tr("Print Document"));
    if (dialog->exec() != QDialog::Accepted)
        return;

    Export exporter = initExporter();

    exporter.print(&printer);*/
}



void MainWindow::openHelp()
{
    if(!jpconjhelp::exists()){
        jpconjhelp* helpWindow = new jpconjhelp(this);
        helpWindow->show();
    }
}



void MainWindow::zoom(signed char sign)
{
    workfrm->zoom(sign);

}




/*!
 * \brief jpconjmain::setCSS Set a user defined CSS to the QWebView
 * \param webView The QWebView we want to set the content CSS.
 * \param nameCSS The name of the CSS located in <dataFolder>/styles/ with the extension ".css"
 */
void MainWindow::setCSS(QWebView * webView, QString nameCSS)
{
    /*QString cssfile = "file:" + QDir(QString(dataFolder)).absolutePath() + "/styles/" + nameCSS;
    QWebSettings * settings = webView->settings();
    settings->setUserStyleSheetUrl(QUrl(cssfile));*/
}



/*!
 * \brief jpconjmain::setHTMLDirection Set the direction of the webView body.
 */
void MainWindow::setHTMLTranslation(bool rtl)
{

    if (!languageChanged)
        return;

    workfrm->refreshLanguage(rtl);

    languageChanged = false;
}



void MainWindow::createTryIcon()
{
    //System tray Icon
    QAction *actionHelpContent = ui->actionHelpContent;
    trayIconSys->addAction(actionHelpContent);
    QAction *actionClose = ui->actionClose;
    trayIconSys->addAction(actionClose);
    trayIconSys->hideMain();

}

/*******************************************************
 *                    PROTECTED
 *******************************************************/

/*!
 * \brief jpconjmain::changeEvent The event treated here is the change of language.
 * \param event
 */
void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        //Msg::updateMsg();
        ui->retranslateUi(this);
        bool rtl=Language::mainWindowDirection(this);
        languageChanged = true;
        setHTMLTranslation(rtl);
        actionShow->setText(tr("Show"));
        //qDebug()<< "changed";
    }
    QMainWindow::changeEvent(event);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //trayIcon->hideMain();
    createTryIcon();
    event->ignore();
    //qApp->quit();

}

/*******************************************************
 *                   PRIVATE SLOTS
 *******************************************************/

void MainWindow::changeStyle(QString styleID)
{
    stylesheet = styleID + ".css";
    workfrm->changeStyle(styleID);
}

void MainWindow::on_actionClose_triggered()
{
    qApp->quit();
}


void MainWindow::on_actionAbout_triggered()
{
    openAbout();
}

void MainWindow::on_actionPreference_triggered()
{
    openPref();
}

void MainWindow::on_actionHelpContent_triggered()
{
    openHelp();
}



void MainWindow::on_actionExportResult_triggered()
{
    //doExport();
}

void MainWindow::on_actionPrint_triggered()
{
    //doPrint();
}

void MainWindow::on_actionZoomIn_triggered()
{
    zoom(1);
}

void MainWindow::on_actionZoomOut_triggered()
{
    zoom(-1);
}

void MainWindow::on_actionNormalSize_triggered()
{
    zoom(0);
}

void MainWindow::on_actionHide_triggered()
{
    createTryIcon();
}

void MainWindow::on_actionContactUs_triggered()
{
    QDesktopServices::openUrl(QUrl("mailto:dzcoding@googlegroups.com"));
}

void MainWindow::on_actionHomePage_triggered()
{
    QDesktopServices::openUrl(QUrl("http://japkatsuyou.sourceforge.net"));
}
