#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include<QSerialPort>
#include<QSerialPortInfo>

extern QSerialPort *serial;


QT_CHARTS_USE_NAMESPACE
class HandleData : public QObject
{
    Q_OBJECT

public:
    explicit HandleData(QObject *parent = 0);

signals:
    void sendCCDGray(uchar ccd);

public:
    void showGray();

public slots:
//  void receiveccdifo(uchar ccd);

public:
    uchar ccdGray[128]={0};
    uchar ccdBinary[128]={0};
    QLineSeries *series;
    QChart *chart;
    QImage ccdGrap=QImage(128,1,QImage::Format_Grayscale8);
    QValueAxis grayYAxis;
    QValueAxis grayXAxis;
    QGraphicsScene *scene;
};

#endif // HANDLEDATA_H
