#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);//禁止缩放
    setFixedSize(this->width(), this->height());

    //查找可用串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }

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


//清空接受窗口
void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

//发送数据
void MainWindow::on_sendButton_clicked()
{
    serial->write(ui->textEdit_2->toPlainText().toLatin1());
}

//读取接收到的数据
void MainWindow::Read_Data()
{
    if(Qt::Checked==ui->checkBoxView->checkState())
    {
        QByteArray buf;
        buf = serial->readAll();
        if((QByteArray)NULL !=buf)
        {
            QString str = ui->textEdit->toPlainText();
            str+=tr(buf);
            ui->textEdit->clear();
            ui->textEdit->append(str);
        }
        buf.clear();
    }
}


void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        //设置数据位数
        switch(ui->BitNumBox->currentIndex())
        {
        case 8: serial->setDataBits(QSerialPort::Data8); break;
        default: break;
        }
        //设置奇偶校验
        switch(ui->ParityBox->currentIndex())
        {
        case 0: serial->setParity(QSerialPort::NoParity); break;
        default: break;
        }
        //设置停止位
        switch(ui->StopBox->currentIndex())
        {
        case 1: serial->setStopBits(QSerialPort::OneStop); break;
        case 2: serial->setStopBits(QSerialPort::TwoStop); break;
        default: break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        ui->startCarButton->setText(tr("StartCar"));
        ui->blueTooth->setText(tr("显示波形"));
        ui->sendButton->setEnabled(true);
        ui->btnFindPort->setEnabled(false);

        ui->blueTooth->setEnabled(true);
        ui->steerSendButton->setEnabled(true);
        ui->steerGetButton->setEnabled(true);
        ui->motorGetButton->setEnabled(true);
        ui->motorSendButton->setEnabled(true);
        ui->startCarButton->setEnabled(true);
        ui->modelComboBox->setEnabled(true);

        //CCD图像显示设置

        uchar arr[128]={0};
        for(int ii=0;ii<128;ii++)
        {
            arr[ii]=ii*2;
//            series->append(ii, arr[ii]);
        }

        QImage ccd1Grap=QImage(arr,128,1,QImage::Format_Grayscale8);
        QImage ccd2Grap=QImage(128,1,QImage::Format_Grayscale8);
        ccd1Grap=ccd1Grap.scaled(ui->ccd1GraphicsView->width()-10,ui->ccd1GraphicsView->height()-10);

        qDebug()<<ui->ccd1GraphicsView->height();
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(ccd1Grap));
        ui->ccd1GraphicsView->setScene(scene);
        ui->ccd1GraphicsView->show();
        ui->ccd2GraphicsView->setScene(scene);
        ui->ccd2GraphicsView->show();

        //判断显示CCD曲线信息
//        if(Qt::Checked==ui->ccd1CheckBox->checkState())
//        {

//        }

//        if(Qt::Checked==ui->ccd2CheckBox->checkState());


        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        ui->startCarButton->setText(tr("StartCar"));
        ui->blueTooth->setText(tr("显示波形"));
        ui->sendButton->setEnabled(false);
        ui->btnFindPort->setEnabled(true);

        ui->blueTooth->setEnabled(false);
        ui->steerSendButton->setEnabled(false);
        ui->steerGetButton->setEnabled(false);
        ui->motorGetButton->setEnabled(false);
        ui->motorSendButton->setEnabled(false);
        ui->startCarButton->setEnabled(false);
        ui->modelComboBox->setEnabled(false);
    }
}

 //查找可用的串口
void MainWindow::on_btnFindPort_clicked()
{
        ui->PortBox->clear();
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            QSerialPort serial;
            serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite))
            {
                ui->PortBox->addItem(serial.portName());
                serial.close();
            }
        }
}

//开车
void MainWindow::on_startCarButton_clicked()
{
    if(ui->startCarButton->text()==tr("StartCar"))
    {
        ui->startCarButton->setText(tr("StopCar"));
    }
    else
    {
        ui->startCarButton->setText(tr("StartCar"));
    }
}

void MainWindow::on_blueTooth_clicked()
{
    if(ui->blueTooth->text()==tr("显示波形"))
    {
        ui->blueTooth->setText(tr("关闭波形"));
        ui->webView->load(QUrl("file:///"+qApp->applicationDirPath()+"/html/line.html"));
    }
    else
    {
        ui->blueTooth->setText(tr("显示波形"));
        ui->webView->load(QUrl());
    }
}


//CCD波形显示选择
void MainWindow::on_ccd1CheckBox_clicked()
{
    if(Qt::Checked==ui->ccd1CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
    {
        ui->ccd1ChartView->load(QUrl("file:///"+qApp->applicationDirPath()+"/html/linex.html"));
    }
    else
        ui->ccd1ChartView->load(QUrl());
}

void MainWindow::on_ccd2CheckBox_clicked()
{
    if(Qt::Checked==ui->ccd2CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
    {
        ui->ccd2ChartView->load(QUrl("file:///"+qApp->applicationDirPath()+"/html/linex.html"));
    }
    else
        ui->ccd2ChartView->load(QUrl());
}
