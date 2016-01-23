#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rq = new Requestor();
    rq->connect();
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
