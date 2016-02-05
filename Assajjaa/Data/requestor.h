#ifndef REQUESTOR_H
#define REQUESTOR_H

#include <QString>
#include <QtSql/QtSql>
#include <QDebug>

#include "Data/transformer.h"

class Requestor
{
public:
    Requestor();
    void connect();
    void desconnect();
    void clearRequest();
    void addWazn(QString wazn);
    void addQafiya(QString qafiya);
    void addBegining(QString begin);
    QString getRequest();
    QStringList getResult();

private:
    QSqlDatabase arbdb;
    QString request;
    bool more;

};

#endif // REQUESTOR_H
