#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handledata.h"




void MainWindow::initChart()
{
    //CCD图像初始化
    ui->ccd1GrayView->setChart(ccd1Data.chart);
    ui->ccd1GrayView->setRenderHint(QPainter::Antialiasing);
    ui->ccd1GrayView->show();
    ui->ccd1GraphicsView->setScene(ccd1Data.scene);
    ui->ccd1GraphicsView->show();

    ui->ccd2GrayView->setChart(ccd2Data.chart);
    ui->ccd2GrayView->setRenderHint(QPainter::Antialiasing);
    ui->ccd2GrayView->show();
    ui->ccd2GraphicsView->setScene(ccd2Data.scene);
    ui->ccd2GraphicsView->show();


    Road = new QLineSeries;
    Road->setName("CCD中心");
    DataChart = new QChart;
    DataChart->setTheme(QChart::ChartThemeDark);
    DataChart->addSeries(Road);
    XAxis.setRange(0,128);
    XAxis.setTickCount(4);
//    XAxis.setLabelsVisible(false);
    YAxis.setRange(0,300);
    DataChart->setAxisX(&XAxis,Road);
    DataChart->setAxisY(&YAxis,Road);
    ui->dataView->setChart(DataChart);
    ui->dataView->setRenderHint(QPainter::Antialiasing);
    ui->dataView->show();

//    QPen green(Qt::red);
//    green.setWidth(3);
//    Road->setPen(green);

}


void  MainWindow::showLine(QLineSeries* line, uchar data)
{
//    static qreal m_x=5,m_y=1;
//    qreal x = DataChart->plotArea().width() / XAxis.tickCount();
//    qreal y = (XAxis.max() - XAxis.min()) / XAxis.tickCount();
//    m_x += y;
//    m_y = newdata;
//    line->append(m_x, m_y);
//    DataChart->scroll(x, 0);

//    qint64 range = 128;
//    QVector<QPointF> oldPoints = line->pointsVector();
//    QVector<QPointF> points;
//    int resolution = 1;

//    if (oldPoints.count() < range) {
//        points = line->pointsVector();
//    } else {
//        for (int i = range/resolution; i < oldPoints.count(); i++)
//            points.append(QPointF(i - range/resolution, oldPoints.at(i).y()));
//    }

//    qint64 size = points.count();
//    for (int k = 0; k < range/resolution; k++)
//        points.append(QPointF(k + size, (quint8)data[resolution * k]));

//    line->replace(points);

    static qint64 cnt=0;
    qint64 range = 128;
    if(cnt<range)
        line->append(cnt++,data);
    else
    {
        line->append(cnt++,data);
        DataChart->scroll(1,0);
    }

}

