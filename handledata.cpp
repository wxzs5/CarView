#include "handledata.h"
#include<QDebug>

QSerialPort *serial;

HandleData::HandleData(QObject *parent) : QObject(parent)
{
    //CCD图表信息设置
    series = new QLineSeries;
    chart = new QChart;
    chart->addSeries(series);
    grayYAxis.setRange(0, 256);
    grayXAxis.setRange(0, 128);
    grayXAxis.setLabelFormat("d");
    grayYAxis.setLabelFormat("d");


    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->setBackgroundVisible(false);
    chart->setLocalizeNumbers(true);
    chart->legend()->hide();
    chart->setAxisX(&grayXAxis, series);
    chart->setAxisY(&grayYAxis, series);
    chart->setToolTip("灰度");

    ccdGrap = QImage(this->ccdGray, 128, 1, QImage::Format_Grayscale8);
    scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(ccdGrap));

}

//显示CCD信息
void HandleData::showGray()
{
    series->clear();
    series->hide();
    for (int ii = 0; ii < 128; ii++)
        series->append(ii, ccdGray[ii]);
    series->show();
    scene->clear();
    ccdGrap = QImage(ccdGray, 128, 1, QImage::Format_Grayscale8);
    ccdGrap = ccdGrap.scaled(486, 26);
    scene->addPixmap(QPixmap::fromImage(ccdGrap));
}

void HandleData::serialDataHandle()
{
//    static quint8 RxBuffer[50];
//    static quint8 _data_len = 0, _data_cnt = 0;
//    static quint8 state = 0;

//    if (state == 0 && data == 0xAA)
//    {
//        state = 1;
//        RxBuffer[0] = data;
//    }
//    else if (state == 1 && data == 0xAF)
//    {
//        state = 2;
//        RxBuffer[1] = data;
//    }
//    else if (state == 2 && data < 0XF1)
//    {
//        state = 3;
//        RxBuffer[2] = data;
//    }
//    else if (state == 3 && data < 50)
//    {
//        state = 4;
//        RxBuffer[3] = data;
//        _data_len = data;
//        _data_cnt = 0;
//    }
//    else if (state == 4 && _data_len > 0)
//    {
//        _data_len--;
//        RxBuffer[4 + _data_cnt++] = data;
//        if (_data_len == 0)
//            state = 5;
//    }
//    else if (state == 5)
//    {
//        state = 0;
//        RxBuffer[4 + _data_cnt] = data;
//        ANO_DT_Data_Receive_Anl(RxBuffer, _data_cnt + 5);
//    }
//    else
//        state = 0;
}


//void HandleData::loadGrayData(uchar *ccd, qint8 id)
//{

//}

