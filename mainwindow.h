#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QtWebEngineWidgets/QWebEngineView>
#include<QtWebEngineWidgets/QWebEnginePage>
#include<QtWebChannel>
#include"handledata.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readCCDGrap();
    void initChart();
    void showLine(QLineSeries* line, float data);

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

    void on_variableButton_clicked();

private:
    Ui::MainWindow *ui;
    HandleData ccd1Data;
    HandleData ccd2Data;
    QChart *DataChart;
    QValueAxis YAxis;
    QValueAxis XAxis;
    QLineSeries *Road;
    uchar LineTemp[128]={0};
    quint8 Conmand[23]={0xAA,0xAF};
};

#endif // MAINWINDOW_H
