#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SCU PassCet6");
    w.show();
    return a.exec();
}



//#include <QtWidgets/QApplication>
//#include <QtWidgets/QMainWindow>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>

//QT_CHARTS_USE_NAMESPACE

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

////![1]
//    QLineSeries *series = new QLineSeries();
////![1]

////![2]
//    series->append(0, 6);
//    series->append(2, 4);
//    series->append(3, 8);
//    series->append(7, 4);
//    series->append(10, 5);
//    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
////![2]

////![3]
//    QChart *chart = new QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->createDefaultAxes();
//    chart->setTitle("Simple line chart example");
////![3]

////![4]
//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
////![4]


////![5]
//    QMainWindow window;
//    window.setCentralWidget(chartView);
//    window.resize(400, 300);
//    window.show();
////![5]

//    return a.exec();
//}
