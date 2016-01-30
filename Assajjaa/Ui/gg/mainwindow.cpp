#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rq = new Requestor();
    rq->connect();
    initiateFields();
}

MainWindow::~MainWindow()
{
    rq->desconnect();
    delete ui;
}

void MainWindow::on_srch_clicked()
{

    rq->clearRequest();
    ui->res->clear();

    if (ui->qafia->currentIndex() != 0){
        QString qafiya = ui->qafia->currentText();
        rq->addQafiya(qafiya);
    }

    if (ui->wazn->currentIndex() != 0){
        QString wazn = ui->wazn->currentText();
        rq->addWazn(wazn);
    }

    qDebug()<< rq->getRequest();

    QStringList result = rq->getResult();
    ui->res->addItems(result);

}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::initiateFields()
{
    QFile wazns (QString(LingPath) + "awzan.txt");
    if (wazns.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream txtStream(&wazns);
        txtStream.setCodec("UTF-8");
        while(! txtStream.atEnd()){
            QString wazn = txtStream.readLine().trimmed();

            if (wazn.length() > 0)
                ui->wazn->addItem(wazn);
        }

        qDebug()<< "File wazns found";
    }

    QFile qawafi (QString(LingPath) + "qawafi.txt");
    if (qawafi.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream txtStream(&qawafi);
        txtStream.setCodec("UTF-8");
        while(! txtStream.atEnd()){
            QString qafiya = txtStream.readLine().trimmed();

            if (qafiya.length() > 0)
                ui->qafia->addItem(qafiya);
        }

        //qDebug()<< "File wazns found";
    }
}
