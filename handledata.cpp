#include "handledata.h"
#include<QDebug>

HandleData::HandleData(QObject *parent) : QObject(parent)
{

}

void HandleData::LoadGrayData(uchar *ccd, qint8 id)
{
    if(id==1)
    {
        for(int ii=0;ii<128;ii++)
        this->ccd1Gray[ii]=*ccd++;
    }
    else if(id==2)
    {
        for(int ii=0;ii<128;ii++)
        this->ccd2Gray[ii]=*ccd++;
    }
    else
        qDebug()<<"ccd id is not correct!";
}

