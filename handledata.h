#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <QObject>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE
class HandleData : public QObject
{
    Q_OBJECT
public:
    explicit HandleData(QObject *parent = 0);

    void LoadGrayData(uchar *ccd, qint8 id);

signals:
    void sendCCDGray(uchar ccd);

public:
    void showGray();

public slots:
//  void receiveccdifo(uchar ccd);

public:
    uchar ccdGray[128];
    uchar ccdBinary[128];
    QLineSeries *series;
    QChart *chart;
    QImage ccdGrap=QImage(128,1,QImage::Format_Grayscale8);
    QValueAxis grayYAxis;
    QValueAxis grayXAxis;
    QGraphicsScene *scene;
};

#endif // HANDLEDATA_H
