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
    init.cpp \
    QtSpeech_win.cpp

CONFIG += warn_on
DEFINES += QTSPEECH_STATIC



    INCLUDEPATH += "C:/Program Files/PSDK/Include"
    INCLUDEPATH += "C:/Program Files/PSDK/Include/atl"
    INCLUDEPATH += "C:/Program Files/Microsoft Speech SDK 5.1/Include"

    LIBS += -L"C:/Program Files/Microsoft Speech SDK 5.1/Lib/i386"

    QMAKE_CFLAGS -= -Zc:strictStrings
    QMAKE_CXXFLAGS -= -Zc:strictStrings



HEADERS  += mainwindow.h \
    handledata.h \
    QtSpeech.h \
    QtSpeech

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
