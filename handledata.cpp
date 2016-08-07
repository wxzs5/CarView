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

    ccdGrap = QImage(ccdGray, 128, 1, QImage::Format_Grayscale8);
    ccdGrap = ccdGrap.scaled(486, 26);
    scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(ccdGrap));
}

//显示CCD灰度图
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



