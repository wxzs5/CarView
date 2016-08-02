#include "mainwindow.h"
#include <QApplication>
#include<QWebEngineView>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QIODevice>
#include<QTextCodec>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SCU PassCet6");
    w.show();


//    QWebEngineView view;

//    view.load(QUrl("file:///D:/Project/Qt/EchartDemo/html/line.html"));

//    view.show();
//    view.resize(1024,750);
    return a.exec();
}
