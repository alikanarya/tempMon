#ifndef GPIODS18B20_H
#define GPIODS18B20_H

#define DS18B20_PATH "/sys/devices/w1_bus_master1/"
//#define DS18B20_PATH "/sys/devices/w1_bus_master1/28-80000026a828"
#define DS18B20_READ "/w1_slave"

#include <QObject>
#include <QThread>
#include <QDebug>

class gpioDS18B20 : public QThread {

    Q_OBJECT

public:

    gpioDS18B20();
    ~gpioDS18B20();

    void stop();
    float readDS18B20(int sensor);

    QString ds18b20_SN1;
    float sensor1val = -1;

public slots:


protected:

    void run();

private:

    volatile bool stopped;

signals:

    void readOK();

};

#endif // GPIODS18B20_H
