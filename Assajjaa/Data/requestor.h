#ifndef REQUESTOR_H
#define REQUESTOR_H

#include <QString>
#include <QtSql/QtSql>
#include <QDebug>

class Requestor
{
public:
    Requestor();
    void connect();
    void desconnect();
    void clearRequest();
    void addWazn(QString wazn);
    void addQafiya(QString qafiya);
    QString getRequest();
    QStringList getResult();

private:
    QSqlDatabase arbdb;
    QString request;
    bool more;

};

#endif // REQUESTOR_H
