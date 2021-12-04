#ifndef MYFUNC_H
#define MYFUNC_H

#include <QByteArray>
#include <QBitArray>
#include <QMap>

class MyFunc
{
public:
    MyFunc();
    QByteArray byteToBits(QByteArray x, int pos, int len);
    QByteArray bitsToByte(QBitArray x, int pos, int len);
    QByteArray crcsum(QByteArray in);
    QByteArray crcsum_2num(QByteArray in, QByteArray in2);
    QByteArray crcxor_2num(QByteArray in, QByteArray in2);
    QByteArray crcxor(QByteArray in);
    int byteToInt8(QByteArray x);
    int byteToInt16(QByteArray x);
    int byteToInt(QByteArray x);
    int maxIdx(QMap<int,int> arr);
    //int minVal(QMap<int,QByteArray> arr, int min_pr, int id);
    int minVal(QByteArray arr);
    int minVal2(QByteArray arr, int min_pr, int min_pr_ff);
    int sumVal(QMap<int,int> arr);
    QByteArray korrBits(QByteArray);

};


#endif // MYFUNC_H
