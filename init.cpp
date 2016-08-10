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
//    ui->dataView->setHorizontalScrollBar(ui->dataScrollBar);
//    ui->dataView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    ui->dataScrollBar->setGraphicsEffect();
    ui->dataView->setChart(DataChart);
    ui->dataView->setRenderHint(QPainter::Antialiasing);
    ui->dataView->show();


}


void  MainWindow::showLine(QLineSeries* line, float data)
{
    static qint64 cnt=0;
    qint64 range = 128;
    if(cnt<range)
        line->append(cnt++,data);
    else
    {
        line->append(cnt++,data);
        DataChart->scroll(10,0);
    }

}



//绑定按键
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Enter&&ui->openButton->text()==tr("关闭串口"))
        this->on_startCarButton_clicked();
}




