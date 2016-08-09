#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handledata.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);//禁止缩放
    setFixedSize(this->width(), this->height());

    this->initChart();

    connect(&CheckTime,SIGNAL(timeout()),this,SLOT(CheckSend()));
    //查找可用串口
    this->on_btnFindPort_clicked();
    //默认波特率
    ui->BaudBox->setCurrentIndex(6);
    //关闭发送按钮
    ui->sendButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//清空接收窗口
void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

//发送字符框数据
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

//开车
void MainWindow::on_startCarButton_clicked()
{
    quint8 _cnt = 0;
    Conmand[_cnt++] = 0xAA;
    Conmand[_cnt++] = 0xAF;
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 2;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    CheckTime.start(500);
    Conmand.clear();

    if(ui->startCarButton->text()==tr("StartCar"))
        ui->startCarButton->setText(tr("StopCar"));
    else
        ui->startCarButton->setText(tr("StartCar"));
}

//波形开关
void MainWindow::on_blueTooth_clicked()
{
    if(ui->blueTooth->text()==tr("显示波形"))
    {
        ui->blueTooth->setText(tr("关闭波形"));
//        ui->webView->load(QUrl("file:///"+qApp->applicationDirPath()+"/html/line.html"));
    }
    else
    {
        ui->blueTooth->setText(tr("显示波形"));
//        ui->webView->load(QUrl());
    }
}


//CCD波形显示选择
void MainWindow::on_ccd1CheckBox_clicked()
{
    if(Qt::Checked==ui->ccd1CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
    {
        ccd1Data.showGray();
    }
    else if(Qt::Unchecked==ui->ccd1CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
    {
        ccd1Data.series->hide();
        ccd1Data.scene->clear();
    }
}

void MainWindow::on_ccd2CheckBox_clicked()
{
    if(Qt::Checked==ui->ccd2CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
        ccd2Data.showGray();
    else if(Qt::Unchecked==ui->ccd2CheckBox->checkState()&&ui->openButton->text()==tr("关闭串口"))
    {
        ccd2Data.series->hide();
        ccd2Data.scene->clear();
    }
}

void MainWindow::on_variableButton_clicked()
{
    Road->clear();
}

void MainWindow::on_PIDSend_clicked()
{
    quint8 _cnt = 0;
    quint16 temp;
    Conmand[_cnt++] = 0xAA;
    Conmand[_cnt++] = 0xAF;
    Conmand[_cnt++] = 0x10;
    Conmand[_cnt++] = 18;
    temp=(quint16)(ui->steerPSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Conmand[_cnt++] = 0;
    Conmand[_cnt++] = 0;
    temp=(quint16)(ui->steerDSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->motorPSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->motorISpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->diffSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Conmand[_cnt++] = 0;
    Conmand[_cnt++] = 0;
    temp=(quint16)(ui->steerDSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->steerDSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    CheckTime.start(500);
    Conmand.clear();
}
