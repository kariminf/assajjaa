#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QMap>
#include <QChar>
#include <QDebug>

class Transformer
{
public:
    Transformer();

    static QString BuckwalterTrans(QString arbStr);
    static QString BuckwalterUnTrans(QString transStr);

    static void say();

private:
    static QMap<QChar, QChar> initTrans();

    static const QMap<QChar, QChar> trans;
};

#endif // TRANSFORMER_H
