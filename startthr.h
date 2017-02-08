#ifndef STARTTHR_H
#define STARTTHR_H

#include <QObject>
#include "gpiothread.h"
#include "datathread.h"

extern gpioThread *gpioX;
extern dataThread *dataX;

class startThr : public QObject {

    Q_OBJECT

public:

    explicit startThr(QObject *parent = 0);

signals:

public slots:

    void runRecordData(){
        dataX->cmdRecordData = true;
        dataX->start();
    }

    void runGPIOops(){
        gpioX->start();
    }

};

#endif // STARTTHR_H
