#include "datathread.h"
#include "gpiothread.h"


#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <math.h>

#define MAX 64

extern gpioThread *gpioX;

time_t firstTime, prevTime, currentTime;
struct tm *prevTimeInfo, *currentTimeInfo = new tm();
int timeDiff = 0, timeTotal = 0;
char line[MAX];
char dateInfo[MAX];
char timeInfo[MAX];

void timeString(){
    sprintf (line, "%02d/%02d/%02d, %02d:%02d:%02d, ", 	currentTimeInfo->tm_mday,
                                                (currentTimeInfo->tm_mon+1),
                                                (currentTimeInfo->tm_year-100),
                                                currentTimeInfo->tm_hour,
                                                currentTimeInfo->tm_min,
                                                currentTimeInfo->tm_sec);
    sprintf (dateInfo, "%02d/%02d/%02d", currentTimeInfo->tm_mday, (currentTimeInfo->tm_mon+1), (currentTimeInfo->tm_year-100));
    sprintf (timeInfo, "%02d:%02d:%02d", currentTimeInfo->tm_hour, currentTimeInfo->tm_min, currentTimeInfo->tm_sec);
}

dataThread::dataThread(){

    time (&currentTime);
    currentTimeInfo = localtime (&currentTime);
    firstTime = prevTime = currentTime;

}

dataThread::~dataThread(){
}

void dataThread::prepareFiles(){

    if (fileRecordEnable) {

        for (int i = 0; i < 8; i++){

            if ( !fileExists( zoneNames[i].toUtf8().constData() ) ){

                zones[i].open( zoneNames[i].toUtf8().constData(), ios::out | ios::app );

                if (zones[i].is_open()){
                    zones[i] << fileHeaders[i].toUtf8().constData() << endl;
                    //timeString(); zoneAll << line << "-, -, -, -, -, -, -, -, -" << endl;
                }
            } else
                zones[i].open( zoneNames[i].toUtf8().constData(), ios::out | ios::app );
        }
    }
}

void dataThread::connectToDB(){

    db.setHostName("localhost");
    db.setDatabaseName("homeAutoDB");
    db.setUserName("root");
    db.setPassword("reyhan");
    if (!db.open()) {
        qDebug() <<  db.lastError().text();
    } else {
        qDebug() <<  "db connection established";
    }
}

void dataThread::run(){

    if (!stopped){
    }

    stopped = false;
}

void dataThread::stop(){

    stopped = true;
}

void dataThread::recordData(){

    time (&currentTime);
    currentTimeInfo = localtime (&currentTime);
    //timeDiff = difftime(currentTime, prevTime);
    //timeTotal = difftime(currentTime, firstTime);
    //prevTime = currentTime;
    timeString();

    //cout << line;
    cout << dateInfo << " " << timeInfo << "  ";
    for (int i = 0; i < gpioX->dInpNum; i++)
          cout << gpioX->dInpArr[i] << "   ";
    cout << gpioX->aInpArr[0] << " " << gpioX->aInpArr[1];


    cout << endl;


    if (fileRecordEnable) {

        if (zones[0].is_open()){

            zones[0] << line;
            for (int i = 0; i < gpioX->dInpNum; i++)
                zones[0] << gpioX->dInpArr[i] << ", " ;
            zones[0] << gpioX->aInpArr[0] << ", " << gpioX->aInpArr[1];
            zones[0]<< endl;
        }

        for (int i = 0; i < gpioX->dInpNum; i++) {

            if ( gpioX->dInpArr[i] != gpioX->dInpArrPrev[i] ) {

                if ( zones[i+1].is_open() ){
                    zones[i+1] << line << gpioX->dInpArr[i] << endl;
                }
            }
        }
    }


    if (dbRecordEnable && db.open()) {

        QSqlQuery qry;
        QString cmd;


        cmd = QString( "INSERT INTO %1 (date, time, oto, sln, blk, mut, eyo, cyo, yod) VALUES ('%2', '%3', %4, %5, %6, %7, %8, %9, %10)").arg(tableNames[0]).arg(dateInfo).arg(timeInfo).arg(gpioX->dInpArr[0]).arg(gpioX->dInpArr[1]).arg(gpioX->dInpArr[2]).arg(gpioX->dInpArr[3]).arg(gpioX->dInpArr[4]).arg(gpioX->dInpArr[5]).arg(gpioX->dInpArr[6]);
        //qDebug() << cmd.toUtf8().constData();

        qry.prepare( cmd );

        if( !qry.exec() )
          qDebug() << qry.lastError();


        for (int i = 0; i < gpioX->dInpNum; i++) {

            if ( gpioX->dInpArr[i] != gpioX->dInpArrPrev[i] ) {

                cmd = QString( "INSERT INTO %1 (date, time, state) VALUES ('%2', '%3', %4)").arg(tableNames[i+1]).arg(dateInfo).arg(timeInfo).arg(gpioX->dInpArr[i]);
                //qDebug() << cmd.toUtf8().constData();

                qry.prepare( cmd );

                if( !qry.exec() )
                  qDebug() << qry.lastError();
            }
        }
    }

}
