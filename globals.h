#ifndef GLOBALS_H
#define GLOBALS_H

#include "server.h"
#include "client.h"
#include "datathread.h"
#include "gpiothread.h"

#define INIFILENAME         "settings.ini"
#define _CLIENT_ADR         "localhost"
#define _CLIENT_PORT        8888

QString MSG_SERVER_INIT = "Server is listening...";
QString MSG_CLIENT_CONN = "Client connected";
QString MSG_HI = "Hi by BBB";

QString clientAddress = "";
quint16 clientPort = 0;

bool firstRun = true;




#endif // GLOBALS_H
