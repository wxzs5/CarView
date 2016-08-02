#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>


QT_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("file:///D:/Project/Qt/EchartDemo/html/linex.html"));

    //Find Useable SerialPort
//    const auto infos = QSerialPortInfo::availablePorts();
//    for (const QSerialPortInfo &info : infos)
//        ui->PortBox->addItem(info.portName());

    //Set Default BaudRate
    ui->BaudBox->setCurrentIndex(6);
    //Close SendButton Enable
    ui->sendButton->setEnabled(false);
    qDebug() << tr("UI Setted Successful!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

