#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QtWebEngineWidgets/QWebEngineView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();

    void on_sendButton_clicked();

    void on_openButton_clicked();

    void Read_Data();

    void on_btnFindPort_clicked();



    void on_startCarButton_clicked();

    void on_blueTooth_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
