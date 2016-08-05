#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QtWebEngineWidgets/QWebEngineView>
#include<QtWebEngineWidgets/QWebEnginePage>
#include<QtWebChannel>
#include"handledata.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showGray(qint8 id);
    void readCCDGrap();

private slots:
    void on_clearButton_clicked();

    void on_sendButton_clicked();

    void on_openButton_clicked();

    void Read_Data();

    void on_btnFindPort_clicked();



    void on_startCarButton_clicked();

    void on_blueTooth_clicked();


    void on_ccd1CheckBox_clicked();

    void on_ccd2CheckBox_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    HandleData cardata;
    QLineSeries *series1;
    QLineSeries *series2;
    QChart *chart1;
    QChart *chart2;
    QImage ccd1Grap=QImage(128,1,QImage::Format_Grayscale8);
    QImage ccd2Grap=QImage(128,1,QImage::Format_Grayscale8);
    QValueAxis ccd1GrayYAxis;
    QValueAxis ccd1GrayXAxis;
    QValueAxis ccd2GrayYAxis;
    QValueAxis ccd2GrayXAxis;
};

#endif // MAINWINDOW_H
