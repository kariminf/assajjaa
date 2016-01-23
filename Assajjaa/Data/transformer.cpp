#include "transformer.h"

Transformer::Transformer()
{
}

QString Transformer::BuckwalterTrans(QString arbStr)
{
    QString res = "";
    if (arbStr.size() < trans.size()){
        for(QChar ch : arbStr) {
            res += trans.value(ch);
        }

    } else{
        res = arbStr;
        for(Qchar ch : trans.keys()){

            res = res.replace(ch, trans.value(ch));
        }

    }

    return res;
}

QString Transformer::BuckwalterUnTrans(QString transStr)
{
    QString res = transStr;
    for(Qchar ch : trans.keys()){
        res = res.replace(trans.value(ch), ch);
    }
    return res;
}

void Transformer::say()
{
    qDebug()<< trans.size();
}

const QMap<QChar, QChar> Transformer::trans = initTrans();

QMap<QChar, QChar> Transformer::initTrans()
{
            QMap<QChar, QChar> res;
            res.insert(QChar(0x0627), QChar('A')); // alif
            res.insert(QChar(0x0628), QChar('b')); // ba
            res.insert(QChar(0x062A), QChar('t')); // ta
            res.insert(QChar(0x062B), QChar('v')); // tha
            res.insert(QChar(0x062C), QChar('j')); // jim
            res.insert(QChar(0x062D), QChar('H')); // Ḥa
            res.insert(QChar(0x062E), QChar('x')); // kha
            res.insert(QChar(0x062F), QChar('d')); // dal
            res.insert(QChar(0x0630), QChar('*')); // dhal
            res.insert(QChar(0x0631), QChar('r')); // ra
            res.insert(QChar(0x0632), QChar('z')); // zin
            res.insert(QChar(0x0633), QChar('s')); // sin
            res.insert(QChar(0x0634), QChar('$')); // shin
            res.insert(QChar(0x0635), QChar('S')); // ṣad
            res.insert(QChar(0x0636), QChar('D')); // Ḍad
            res.insert(QChar(0x0637), QChar('T')); // Ṭa
            res.insert(QChar(0x0638), QChar('Z')); // Ẓa
            res.insert(QChar(0x0639), QChar('E')); // 'Ayn
            res.insert(QChar(0x063A), QChar('g')); // ghayn
            res.insert(QChar(0x0641), QChar('f')); // fa
            res.insert(QChar(0x0642), QChar('q')); // qaf
            res.insert(QChar(0x0643), QChar('k')); // kaf
            res.insert(QChar(0x0644), QChar('l')); // lam
            res.insert(QChar(0x0645), QChar('m')); // mim
            res.insert(QChar(0x0646), QChar('n')); // nun
            res.insert(QChar(0x0647), QChar('h')); // ha
            res.insert(QChar(0x0648), QChar('w')); // waw
            res.insert(QChar(0x064A), QChar('y')); // ya
            // hamza
            res.insert(QChar(0x0621), QChar('\'')); // lone hamza
            res.insert(QChar(0x0623), QChar('>')); // hamza on alif
            res.insert(QChar(0x0625), QChar('<')); // hamza below alif
            res.insert(QChar(0x0624), QChar('&')); // hamza on waw
            res.insert(QChar(0x0626), QChar('}')); // hamza on ya
            // alif
            res.insert(QChar(0x0622), QChar('|')); // madda on alif
            res.insert(QChar(0x0671), QChar('{')); // alif alwasla
            res.insert(QChar(0x0670), QChar('`')); // dagger alif
            res.insert(QChar(0x0649), QChar('Y')); // alif maqsura
            // harakat
            res.insert(QChar(0x064E), QChar('a')); // fatha
            res.insert(QChar(0x064F), QChar('u')); // Damma
            res.insert(QChar(0x0650), QChar('i')); // kasra
            res.insert(QChar(0x064B), QChar('F')); // fathatayn
            res.insert(QChar(0x064C), QChar('N')); // dammatayn
            res.insert(QChar(0x064D), QChar('K')); // kasratayn
            res.insert(QChar(0x0651), QChar('~')); // shadda
            res.insert(QChar(0x0640), QChar('_')); // tatwil
            // others
            res.insert(QChar(0x0629), QChar('p')); // ta marbuta
            res.insert(QChar(0x0652), QChar('o')); // sukun
            return res;

}
