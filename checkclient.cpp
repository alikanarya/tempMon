#include "checkclient.h"
#include "client.h"

#include <iostream>

using namespace std;

extern Client *clientx;

checkClient::checkClient(){

    stopped = false;
}

void checkClient::run(){

    if (!stopped){    }
    stopped = false;
    //connect();
}

void checkClient::connect(){

    if (clientx->clientSocket.state() != QAbstractSocket::ConnectingState &&
        clientx->clientSocket.state() != QAbstractSocket::ConnectedState ){
        //cout << "checkClient" << endl;    //DBG
        clientx->start();
    }

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState )
        emit Connected();
    else
        emit notConnected();

}

void checkClient::transferToTCPServer(){

    if (clientx->clientSocket.state() == QAbstractSocket::ConnectedState)
        clientx->startTransfer();
}

void checkClient::stop(){

    stopped = true;

}

checkClient::~checkClient(){
}

