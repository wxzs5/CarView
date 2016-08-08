#-------------------------------------------------
#
# Project created by QtCreator 2016-07-19T00:11:06
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets
QT       += serialport charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets


TARGET = HelloQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    handledata.cpp \
    serialport.cpp \
    init.cpp

HEADERS  += mainwindow.h \
    handledata.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
