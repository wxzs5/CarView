#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handledata.h"



//解析串口
void MainWindow::readCCDGrap()
{
    int ii=0,cnt=0;
    qint64 len=0,read_len=0;
    static QByteArray serialData,restData;
    QByteArray serialTempData=serial->readAll();
    if(!restData.isEmpty())  //添加补足的帧尾
    {
        serialData.append(restData);
        restData.clear();
    }
    serialData.append(serialTempData);
    serialTempData.clear();
    //如果CCD选钮选择，那么就解析CCD，即和解析奔跑数据互斥
    if(Qt::Checked==ui->ccd2CheckBox->checkState()||Qt::Checked==ui->ccd1CheckBox->checkState())
    {
        if(serialData.size()>260)
        {
            len=serialData.size();
            ui->statusBar->showMessage(tr("CCD Data!"),200);
            while(ii<len)
            {
                if(ii<len-130)
                {
                    if(serialData.at(ii)=='*'&&serialData.at(ii+1)=='z')    //CCD1灰度图
                    {
                        ii=ii+2;
                        read_len=128;
                        cnt=0;
                        while(read_len>0)
                        {
                            ccd1Data.ccdGray[cnt++]=(uchar)serialData.at(ii++);
                            read_len--;
                        }
                        if(Qt::Checked==ui->ccd1CheckBox->checkState())
                            ccd1Data.showGray();
                    }
                    else if(serialData.at(ii)=='*'&&serialData.at(ii+1)=='y')//CCD2灰度图
                    {
                        ii=ii+2;
                        read_len=128;
                        cnt=0;
                        while(read_len>0)
                        {
                            ccd2Data.ccdGray[cnt++]=(uchar)serialData.at(ii++);
                            read_len--;
                        }
                        if(Qt::Checked==ui->ccd2CheckBox->checkState())
                            ccd2Data.showGray();
                    }
                    else
                    {
                        ii++;
                    }
                }
                else
                {
                    restData=serialData.mid(ii,len);
                    break;
                }
            }  //while()
            serialData.clear();  //只有解析完才清数据
        }
    }
    else//解析奔跑数据
    {
        len=serialData.size();
        for(ii=0;ii<len-18;ii++)
        {
            if((quint8)serialData.at(ii)==0xAA&&(quint8)serialData.at(ii+1)==0xAA)  //数据帧帧头解析成功
            {
                if((quint8)serialData.at(ii+2)==0xEF)     //校验帧
                {
                    CheckHead=serialData.at(ii+4);
                    ReceiveCheck=serialData.at(ii+5);
                    if(CheckHead==0x11)
                    {
                        if(CheckSpeed==ReceiveCheck)
                        {
                            ui->statusBar->showMessage("Speed Successful!",800);
                            this->speech.tell("Send Successful!");
                            SendSuccessFlag=1;
                        }
                    }
                    else if(CheckHead==0x10)
                    {
                        if(CheckPID==ReceiveCheck)
                        {
                            ui->statusBar->showMessage("PID Successful!",800);
                            this->speech.tell("Send Successful!");
                            SendSuccessFlag=1;
                            this->sendSpeed();
                        }
                    }

                }
                else if((quint8)serialData.at(ii+2)==0x10)     //返回的参数
                {
                    double tempdata;
                    tempdata=0.001*((quint8)serialData.at(ii+4)*256+(quint8)serialData.at(ii+5));
                    ui->steerPSpinBox->setValue(tempdata);
                    tempdata=0.001*((quint8)serialData.at(ii+6)*256+(quint8)serialData.at(ii+7));
                    ui->steerDSpinBox->setValue(tempdata);
                    tempdata=0.001*((quint8)serialData.at(ii+8)*256+(quint8)serialData.at(ii+9));
                    ui->motorPSpinBox->setValue(tempdata);
                    tempdata=0.001*((quint8)serialData.at(ii+10)*256+(quint8)serialData.at(ii+11));
                    ui->motorISpinBox->setValue(tempdata);
                    tempdata=0.0001*((quint8)serialData.at(ii+12)*256+(quint8)serialData.at(ii+13));
                    ui->diffSpinBox->setValue(tempdata);
                    ui->speedSpinBox->setValue((quint8)serialData.at(ii+14)*256+(quint8)serialData.at(ii+15));
                    tempdata=((quint8)serialData.at(ii+16)*256+(quint8)serialData.at(ii+17));
                    ui->shiftSpinBox->setValue(tempdata);
                    ii=ii+17;
                }
                else if((quint8)serialData.at(ii+2)==0x12)     //返回的速度值
                {
                    ui->straightSpeed->setValue((quint8)serialData.at(ii+4));
                    ui->CurveSpeed->setValue((quint8)serialData.at(ii+5));
                    ui->snakeSpeed->setValue((quint8)serialData.at(ii+6));
                    ui->obstacleSpeed->setValue((quint8)serialData.at(ii+7));
                    ui->rampUpSpeed->setValue((quint8)serialData.at(ii+8));
                    ui->rampDownSpeed->setValue((quint8)serialData.at(ii+9));
                    ui->intoCurveSpeed->setValue((quint8)serialData.at(ii+10));
                    ii=ii+10;
                }
                else if((quint8)serialData.at(ii+2)==2)     //常规帧
                {
//                          mytemp=(float)((serialData.at(ii+4)*16+serialData.at(ii+5)));
                }
            }
        }
        restData=serialData.mid(ii,len);
        serialData.clear();
    }


}//串口解析函数





//打开/关闭串口
void MainWindow::on_openButton_clicked()
{
    ui->startCarButton->setShortcutEnabled(true);
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
        //设置串口缓冲区大小


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
        ui->PIDGet->setEnabled(true);
        ui->PIDSend->setEnabled(true);
        ui->startCarButton->setEnabled(true);
        ui->modelComboBox->setEnabled(true);

        ui->allSend->setEnabled(true);
        ui->speedSend->setEnabled(true);
        ui->sendThreshold->setEnabled(true);
        ui->getInfomation->setEnabled(true);

        //判断显示CCD曲线信息
        if(Qt::Checked==ui->ccd1CheckBox->checkState())
            ccd1Data.showGray();
        if(Qt::Checked==ui->ccd2CheckBox->checkState())
            ccd2Data.showGray();
        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::readCCDGrap);
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
        ui->PIDGet->setEnabled(false);
        ui->PIDSend->setEnabled(false);
        ui->startCarButton->setEnabled(false);
        ui->modelComboBox->setEnabled(false);

        ui->allSend->setEnabled(false);
        ui->speedSend->setEnabled(false);
        ui->sendThreshold->setEnabled(false);
        ui->getInfomation->setEnabled(false);
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
    quint8 _cnt = 0;
    Conmand[_cnt++] = 0xAA;   //0xAA
    Conmand[_cnt++] = 0xAF;   //0xAF
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 2;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    Conmand.clear();

    if(ui->startCarButton->text()==tr("StartCar"))
        ui->startCarButton->setText(tr("StopCar"));
    else
        ui->startCarButton->setText(tr("StartCar"));
}


//发送基本参数
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
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    temp=(quint16)(ui->steerDSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->motorPSpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->motorISpinBox->value()*1000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    temp=(quint16)(ui->diffSpinBox->value()*10000+30000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    CheckPID=Check;
    Conmand.clear();
    CheckTime.start(400);
}

//发送速度
void MainWindow::sendSpeed()
{
    quint8 _cnt = 0;
    quint16 temp;
    Conmand[_cnt++] = 0xAA;
    Conmand[_cnt++] = 0xAF;
    Conmand[_cnt++] = 0x11;
    Conmand[_cnt++] = 18;
    temp=(quint16)(ui->speedSpinBox->value()+1000);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    temp=(quint16)(ui->shiftSpinBox->value()+100);
    Conmand[_cnt++] = (quint8)(temp>>8);
    Conmand[_cnt++] = (quint8)(temp&0xff);
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Conmand[_cnt++] = 255;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    CheckSpeed=Check;
    Conmand.clear();
    CheckTime.start(400);
}

//获取PID
void MainWindow::on_PIDGet_clicked()
{
    quint8 _cnt = 0;
    Conmand[_cnt++] = 0xAA;   //0xAA
    Conmand[_cnt++] = 0xAF;   //0xAF
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 7;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    Conmand.clear();
}



void MainWindow::CheckSend()
{
    CheckTime.stop();
    if(SendSuccessFlag==1)
    {
        SendSuccessFlag=0;
    }
    else
    {
        ui->statusBar->showMessage("Send Failed",800);
        this->speech.tell("Send Failed!");
    }

}

//获取速度信息
void MainWindow::on_getInfomation_clicked()
{
    quint8 _cnt = 0;
    Conmand[_cnt++] = 0xAA;   //0xAA
    Conmand[_cnt++] = 0xAF;   //0xAF
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 1;
    Conmand[_cnt++] = 6;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    Conmand.clear();
}



void MainWindow::on_speedSend_clicked()
{
    quint8 _cnt = 0;
    Conmand[_cnt++] = 0xAA;
    Conmand[_cnt++] = 0xAF;
    Conmand[_cnt++] = 0x12;
    Conmand[_cnt++] = 8;
    Conmand[_cnt++] = (quint8)(ui->straightSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->CurveSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->snakeSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->obstacleSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->rampUpSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->rampDownSpeed->value());
    Conmand[_cnt++] = (quint8)(ui->intoCurveSpeed->value());
    Conmand[_cnt++] = 0;
    Check = 0;
    for (quint8 i = 0; i < _cnt; i++)
        Check += Conmand[i];
    Conmand[_cnt++] = Check;
    serial->write(Conmand);
    Conmand.clear();
}

