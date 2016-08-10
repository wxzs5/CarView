#include "mainwindow.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon appIcon=QIcon(":/images/AppIcon");
    w.setWindowTitle("SCU PassCet6");
    w.setWindowIcon(appIcon);
    w.show();
    return a.exec();
}



