#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "Data/requestor.h"
#include "Data/transformer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_srch_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    Requestor *rq;
};

#endif // MAINWINDOW_H
