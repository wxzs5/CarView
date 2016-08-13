#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handledata.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint); //禁止缩放
    setFixedSize(this->width(), this->height());

    this->initChart();
    connect(&CheckTime, SIGNAL(timeout()), this, SLOT(CheckSend()));
    //查找可用串口
    this->on_btnFindPort_clicked();
    //默认波特率
    ui->BaudBox->setCurrentIndex(6);

    ui->startCarButton->setShortcutAutoRepeat(false);
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
    if (Qt::Checked == ui->checkBoxView->checkState())
    {
        QByteArray buf;
        buf = serial->readAll();
        if ((QByteArray)NULL != buf)
        {
            QString str = ui->textEdit->toPlainText();
            str += tr(buf);
            ui->textEdit->clear();
            ui->textEdit->append(str);
        }
        buf.clear();
    }
}



//波形开关
void MainWindow::on_blueTooth_clicked()
{
    if (ui->blueTooth->text() == tr("显示波形"))
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
    if (Qt::Checked == ui->ccd1CheckBox->checkState() && ui->openButton->text() == tr("关闭串口"))
    {
        ccd1Data.showGray();
    }
    else if (Qt::Unchecked == ui->ccd1CheckBox->checkState() && ui->openButton->text() == tr("关闭串口"))
    {
        ccd1Data.series->hide();
        ccd1Data.scene->clear();
    }
}

void MainWindow::on_ccd2CheckBox_clicked()
{
    if (Qt::Checked == ui->ccd2CheckBox->checkState() && ui->openButton->text() == tr("关闭串口"))
        ccd2Data.showGray();
    else if (Qt::Unchecked == ui->ccd2CheckBox->checkState() && ui->openButton->text() == tr("关闭串口"))
    {
        ccd2Data.series->hide();
        ccd2Data.scene->clear();
    }
}


//读取参数
void MainWindow::on_readParameter_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "Document files (*.json);;All files(*.*)");
    if (!filename.isNull())
    {
        QFile parameter(filename);
        if (!parameter.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qWarning("Couldn't open json file.");
            return;
        }
        QTextStream ParameterData(&parameter); // 将文本流读取到字符串中：
        QString Para = ParameterData.readAll();
        // 关闭文本流：
        parameter.close();
        QJsonDocument ParaDoc(QJsonDocument::fromJson(Para.toUtf8()));
        if (!ParaDoc.isEmpty())
        {
            QJsonObject ParaObj = ParaDoc.object();
            ui->steerPSpinBox->setValue(ParaObj.value("SteerP").toDouble());
            ui->steerDSpinBox->setValue(ParaObj.value("SteerD").toDouble());
            ui->motorPSpinBox->setValue(ParaObj.value("MotorP").toDouble());
            ui->motorISpinBox->setValue(ParaObj.value("MotorI").toDouble());
            ui->diffSpinBox->setValue(ParaObj.value("Diff").toDouble());
            ui->shiftSpinBox->setValue(ParaObj.value("Shift").toInt());
            ui->speedSpinBox->setValue(ParaObj.value("SpeedExp").toInt());
            ui->timeSpinBox->setValue(ParaObj.value("DebugTime").toInt());
            ui->startLineSpinBox->setValue(ParaObj.value("StartLine").toInt());
            ui->straightSpeed->setValue(ParaObj.value("StraighSpe").toInt());
            ui->straightThreshold->setValue(ParaObj.value("StraighThr").toInt());
            ui->CurveSpeed->setValue(ParaObj.value("CurSpe").toInt());
            ui->intoCurveSpeed->setValue(ParaObj.value("IntoCurSPe").toInt());
            ui->CurveThreshold->setValue(ParaObj.value("IntoCurThr").toInt());
            ui->CurveThresholdUp->setValue(ParaObj.value("IntoCurThrUp").toInt());
            ui->obstacleSpeed->setValue(ParaObj.value("ObstacleSpe").toInt());
            ui->obstacleThreshold->setValue(ParaObj.value("ObstacleThr").toInt());
            ui->obstacleThresholdUp->setValue(ParaObj.value("ObstacleThrUp").toInt());
            ui->rampUpSpeed->setValue(ParaObj.value("RampUpSpe").toInt());
            ui->rampDownSpeed->setValue(ParaObj.value("RampDownSPe").toInt());
            ui->intoCurveTime->setValue(ParaObj.value("IntoCurTime").toInt());
        }
    }
}

void MainWindow::on_saveParameter_clicked()
{
    QJsonObject json;
    json.insert("SteerP", ui->steerPSpinBox->value());
    json.insert("SteerD", ui->steerDSpinBox->value());
    json.insert("MotorP", ui->motorPSpinBox->value());
    json.insert("MotorI", ui->motorISpinBox->value());
    json.insert("Diff",   ui->diffSpinBox->value());
    json.insert("Shift",  ui->shiftSpinBox->value());
    json.insert("SpeedExp", ui->speedSpinBox->value());
    json.insert("DebugTime", ui->timeSpinBox->value());
    json.insert("StartLine", ui->startLineSpinBox->value());
    json.insert("StraighSpe", ui->straightSpeed->value());
    json.insert("StraighThr", ui->straightThreshold->value());
    json.insert("CurSpe",     ui->CurveSpeed->value());
    json.insert("IntoCurSPe", ui->intoCurveSpeed->value());
    json.insert("IntoCurThr", ui->CurveThreshold->value());
    json.insert("IntoCurThrUp", ui->CurveThresholdUp->value());
    json.insert("ObstacleSpe", ui->obstacleSpeed->value());
    json.insert("ObstacleThr", ui->obstacleThreshold->value());
    json.insert("ObstacleThrUp", ui->obstacleThresholdUp->value());
    json.insert("RampUpSpe", ui->rampUpSpeed->value());
    json.insert("RampDownSPe", ui->rampDownSpeed->value());
    json.insert("IntoCurTime", ui->intoCurveTime->value());


    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);

    QString filename = QFileDialog::getSaveFileName(this, "Open Document", QDir::currentPath(), "Document files (*.json)");
    if (!filename.isNull())
    {
        QFile newjson(filename);
        if (!newjson.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::warning(this, "sdf", "can't open", QMessageBox::Yes);
        }
        QTextStream in(&newjson);
        in << json_str;
        newjson.close();
    }

}
