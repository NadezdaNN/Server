#include "myfunc.h"

#include <QBitArray>
#include <math.h>
#include <QDataStream>
#include <QString>
#include <QDebug>


MyFunc::MyFunc()
{
}

QByteArray MyFunc::crcsum(QByteArray in)
{
    QBitArray tmp(8), sum(8), sum_tmp(8);
    sum.fill(false);
    sum_tmp.fill(false);
    int fl;

    for (int b=0; b<in.size(); b++)
    {
        fl=0;
        for (int i=0; i<8; i++)
            tmp.setBit(i,in.at(b)&(1<<i));

        for (int i=0; i<8; i++)
        {
            if (sum_tmp.at(i)==false && tmp.at(i)==false)
            {
                if (fl==0)
                    sum[i]=false;
                else
                {
                    sum[i]=true;
                    fl=0;
                }
            }
            if (sum_tmp.at(i)==false && tmp.at(i)==true)
            {
                if (fl==0)
                    sum[i]=true;
                else
                {
                    sum[i]=false;
                    fl=1;
                }
            }
            if (sum_tmp.at(i)==true && tmp.at(i)==false)
            {
                if (fl==0)
                    sum[i]=true;
                else
                {
                    sum[i]=false;
                    fl=1;
                }
            }
            if (sum_tmp.at(i)==true && tmp.at(i)==true)
            {
                if (fl==0)
                {
                    sum[i]=false;
                    fl=1;
                }
                else
                {
                    sum[i]=true;
                    fl=1;
                }
            }
        }
        sum_tmp=sum;
    }
    return bitsToByte(sum,0,8);
}

QByteArray MyFunc::crcxor(QByteArray in) // исключающее или
{
    QBitArray tmp(8), sum(8), sum_tmp(8);
    sum.fill(false);
    sum_tmp.fill(false);

    for (int b=0; b<in.size(); b++)
    {
        for (int i=0; i<8; i++)
            tmp.setBit(i,in.at(b)&(1<<i));

        for (int i=0; i<8; i++)
        {
            if (sum_tmp.at(i)==false && tmp.at(i)==false)
                sum[i]=false;
            if (sum_tmp.at(i)==false && tmp.at(i)==true)
                sum[i]=true;
            if (sum_tmp.at(i)==true && tmp.at(i)==false)
                sum[i]=true;
            if (sum_tmp.at(i)==true && tmp.at(i)==true)
                sum[i]=false;
        }
        sum_tmp=sum;
    }
    return bitsToByte(sum,0,8);
}

QByteArray MyFunc::byteToBits(QByteArray x, int pos, int len)
{
    QBitArray tmp(8);
    QByteArray out;
    for (int b=0; b<8; b++)
        tmp.setBit(b,x.at(0)&(1<<b));

    out[0]=tmp.at(pos);
    for (int i=1; i<len; i++)
        out[0]=out[0]|(tmp.at(pos+i)<<i);

    return out;
}

QByteArray MyFunc::bitsToByte(QBitArray x, int pos, int len)
{
    QByteArray out;
    out[0]=x.at(pos);
    for (int i=1; i<len; i++)
        out[0]=out[0]|(x.at(pos+i)<<i);

    return out;
}

int MyFunc::byteToInt8(QByteArray x)
{
    QDataStream str(x);
    quint8 foo;
    str>>foo;
    int out;
    out=foo;
    return out;
}

int MyFunc::byteToInt16(QByteArray x)
{
    QDataStream str(x);
    quint16 foo;
    str>>foo;
    int out;
    out=foo;
    return out;
}
int MyFunc::byteToInt(QByteArray x)
{
    int out, Len, w;
    QString s;
    bool ok;
    out=0;
    Len=x.size()*2;
    for (int i=0; i<Len; i++)
    {
        s=char(x.toHex().at(i));
        w=s.toInt(&ok,16);
        out+=w*pow(16.0,Len-1-i);
    }
    return out;
}

int MyFunc::maxIdx(QMap<int,int> arr)
{
    QMap<int, int>::const_iterator i = arr.constBegin();
    int max=i.value();
    int idx=i.key();
//qDebug()<<"begin  "<<idx<<arr.size();
    i++;
    while (i != arr.constEnd())
    {
        if ((i.value())>max)
        {
            max=i.value();
            idx=i.key();
        }
        i++;
    }
//qDebug()<<idx;
    return idx;
}

/*int MyFunc::minVal(QMap<int,QByteArray> arr, int min_pr, int id)
{
    QMap<int, QByteArray>::const_iterator i = arr.constBegin();
    int min=byteToInt(i.value());

    i++;
    while (i != arr.constEnd())
    {
        if (min>=min_pr)
        {
            if (byteToInt(i.value())<min && byteToInt(i.value())>=min_pr)
                min=byteToInt(i.value());
        }
        else
            min=byteToInt(i.value());
        i++;
    }

    if (min>=min_pr)
    {
        //if (min_pr!=0 && (min-min_pr)>4)
            //return min_pr;
        //else
            return min;
    }
    else
        return 0;
}*/

int MyFunc::minVal2(QByteArray arr, int min_pr, int min_pr_ff)
{
    int min=byteToInt(arr.mid(0,3));
    if (arr.mid(0,1).toHex()!="ff")
    {
        for (int i=0; i<arr.size()/3; i++)
        {
            if (byteToInt(arr.mid(i*3,3))<min && byteToInt(arr.mid(i*3,3))>min_pr)
                 min=byteToInt(arr.mid(i*3,3));
        }
        if (min<min_pr && min_pr!=0)
            min=min_pr;
    }
    else
    {
        for (int i=0; i<arr.size()/3; i++)
        {

            if (byteToInt(arr.mid(i*3,3))>min && byteToInt(arr.mid(i*3,3))<min_pr_ff)
                 min=byteToInt(arr.mid(i*3,3));
        }
        if (min>min_pr_ff && min_pr_ff!=0)
            min=min_pr_ff;
    }
    return min;
}

int MyFunc::minVal(QByteArray arr)
{
    int min=byteToInt(arr.mid(0,3));
    if (arr.mid(0,1).toHex()!="ff")
    {
        for (int i=1; i<arr.size()/3; i++)
        {
            if (byteToInt(arr.mid(i*3,3))<min)
                 min=byteToInt(arr.mid(i*3,3));
        }
    }
    else
    {
        for (int i=1; i<arr.size()/3; i++)
        {
            if (byteToInt(arr.mid(i*3,3))>min)
                 min=byteToInt(arr.mid(i*3,3));
        }
    }
    return min;
}


int MyFunc::sumVal(QMap<int,int> arr)
{
    int sum=0;
    QMap<int, int>::const_iterator i = arr.constBegin();
    while (i != arr.constEnd())
    {
        sum=sum+i.value();
        ++i;
    }
    return sum;
}

QByteArray MyFunc::crcsum_2num(QByteArray in, QByteArray in2)
{
    QBitArray tmp(8), tmp2(8), sum(8);
    sum.fill(false);
    int fl=0;

    for (int i=0; i<8; i++)
    {
        tmp.setBit(i,in.at(0)&(1<<i));
        tmp2.setBit(i,in2.at(0)&(1<<i));
    }

    for (int i=0; i<8; i++)
    {
        if (tmp.at(i)==false && tmp2.at(i)==false)
        {
            if (fl==0)
                sum[i]=false;
            else
            {
                sum[i]=true;
                fl=0;
            }
        }

        if (tmp.at(i)==false && tmp2.at(i)==true)
        {
            if (fl==0)
                sum[i]=true;
            else
            {
                sum[i]=false;
                fl=1;
            }
        }

        if (tmp.at(i)==true && tmp2.at(i)==false)
        {
            if (fl==0)
                sum[i]=true;
            else
            {
                sum[i]=false;
                fl=1;
            }
        }

        if (tmp.at(i)==true && tmp2.at(i)==true)
        {
            if (fl==0)
            {
                sum[i]=false;
                fl=1;
            }
            else
            {
                sum[i]=true;
                fl=1;
            }
        }
    }

    return bitsToByte(sum,0,8);
}

QByteArray MyFunc::crcxor_2num(QByteArray in, QByteArray in2) // исключающее или
{
    QBitArray tmp(8), tmp2(8), sum(8), sum_tmp(8);
    sum.fill(false);
    sum_tmp.fill(false);


    for (int i=0; i<8; i++)
    {
        tmp.setBit(i,in.at(0)&(1<<i));
        tmp2.setBit(i,in2.at(0)&(1<<i));
    }

    for (int i=0; i<8; i++)
    {
        if (tmp.at(i)==false && tmp2.at(i)==false)
            sum[i]=false;
        if (tmp.at(i)==false && tmp2.at(i)==true)
            sum[i]=true;
        if (tmp.at(i)==true && tmp2.at(i)==false)
            sum[i]=true;
        if (tmp.at(i)==true && tmp2.at(i)==true)
            sum[i]=false;
    }

    return bitsToByte(sum,0,8);
}

QByteArray MyFunc::korrBits(QByteArray in)
{
    QBitArray tmp(8);

    for (int i=0; i<8; i++)
        tmp.setBit(i,in.at(0)&(1<<i));
    tmp[6]=false;
    tmp[7]=false;

    return bitsToByte(tmp,0,8);
}

