#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <QObject>
#include <QQueue>

class HandleData : public QObject
{
    Q_OBJECT
public:
    explicit HandleData(QObject *parent = 0);

    void LoadGrayData(uchar *ccd, qint8 id);

signals:
    void sendCCDGray(uchar ccd);

public:
    uchar ccd1Gray[128];
    uchar ccd2Gray[128];
    uchar ccd1Binary[128];
    uchar ccd2Binary[128];


public slots:
//  void receiveccdifo(uchar ccd);

private:

};

#endif // HANDLEDATA_H
