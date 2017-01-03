#include <QCoreApplication>
#include <QtNetwork>
#include <iostream>

#include "globals.h"

using namespace std;

Server *serverx;
Client *clientx;
gpioThread *gpioX;
dataThread *dataX;

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    serverx = new Server();
    clientx = new Client();
    gpioX = new gpioThread();
    dataX = new dataThread();

    if (argc == 1){

        dataX->fileRecordEnable = false;
        dataX->dbRecordEnable = false;

    } else if (argc == 2){

        if ( std::string(argv[1]) == "fs" ) dataX->fileRecordEnable = true;
        else if ( std::string(argv[1]) == "db" ) dataX->dbRecordEnable = true;
        else goto label;

    } else if (argc == 3){

        if ( std::string(argv[1]) == "fs" ) dataX->fileRecordEnable = true;
        else if ( std::string(argv[1]) == "db" ) dataX->dbRecordEnable = true;
        else goto label;

        if ( std::string(argv[2]) == "fs" ) dataX->fileRecordEnable = true;
        else if ( std::string(argv[2]) == "db" ) dataX->dbRecordEnable = true;
        else goto label;

    } else {
        label:
        printf("Usage: %s mode\n",argv[0]);
        printf("mode: 'fs' (file save) AND / OR 'db' (database record) \n");

        if (argc == 2) cout << "p1: " << argv[1] << endl;
        if (argc == 3) cout << "p1: " << argv[1] << " p2: " << argv[2] << endl;

        return 1;
    }

    //cout << gpioX->PWMCHIP0_PATH.toUtf8().constData() << endl;
    //cout << gpioX->PWMCHIP1_PATH.toUtf8().constData() << endl;

    if (dataX->fileRecordEnable) dataX->prepareFiles();
    if (dataX->dbRecordEnable) dataX->connectToDB();

    printf("__Date_____Time___OtO_SLN_BLK_MUT_EYO_CYO_YOD__T1___T2");
    cout << endl;


    QObject::connect(serverx, SIGNAL(readFinished()), gpioX, SLOT(enableWrite()));
    QObject::connect(gpioX, SIGNAL(gpioOpsFinished()), dataX, SLOT(recordData()));

    // 1sec timer
    QTimer *timerSec = new QTimer();
    QObject::connect(timerSec, SIGNAL(timeout()), gpioX, SLOT(gpioOps()));
    timerSec->start(1000);



    return app.exec();
}

