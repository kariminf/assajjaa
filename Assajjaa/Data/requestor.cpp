#include "requestor.h"

Requestor::Requestor()
{
    clearRequest();
}


void Requestor::connect()
{
    if (!QSqlDatabase::contains("arbdb"))
    {
        arbdb =  QSqlDatabase::addDatabase("QSQLITE","arbdb");
        arbdb.setDatabaseName(QString(arbDbPath));
        qDebug()<< arbdb.databaseName();
    }
    else
    {
        arbdb =  QSqlDatabase::database("arbdb");
    }
}

void Requestor::desconnect()
{
    if (QSqlDatabase::contains("arbdb"))
        {
            QSqlDatabase::removeDatabase("arbdb");
    }
}

void Requestor::clearRequest()
{
    request  = "SELECT vocalized \n";
    request += "FROM words \n";
    more = false;

}

void Requestor::addWazn(QString wazn)
{
    if (more){
        request += "AND ";
    } else {
        request += "WHERE ";
    }

    //request += "pattern = '" + Transformer::BuckwalterTrans(wazn) + "'\n";
    request += "instr(pattern, '+" + Transformer::BuckwalterTrans(wazn) + "+')>0\n";
    more = true;
}

void Requestor::addQafiya(QString qafiya)
{
    if (more){
        request += "AND ";
    } else {
        request += "WHERE ";
    }

    int len = qafiya.length();
    request += "substr(word,length(word)-" + QString::number(len-1) + "," + QString::number(len) + ") = '" + qafiya + "'\n";
    more = true;
}

QString Requestor::getRequest()
{
    return request;
}

QStringList Requestor::getResult()
{

    QStringList result;
    if (arbdb.open()) {

        QSqlQuery query(arbdb);
        query.exec(request);
        //QSqlRecord record = query.record();

        while(query.next()){
            QString res = query.value(0).toString();//record.indexOf("vocalized")
            result.append(res);
        }

        arbdb.close();

    }

    return result;

}


