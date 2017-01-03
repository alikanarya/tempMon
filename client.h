#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client: public QObject{

    Q_OBJECT

public:

    Client(QObject* parent = 0);
    ~Client();
    void start();

    QTcpSocket clientSocket;
    quint16 clientPort = 8888;

    QString clientAddress = "192.168.2.222"; // Windows ***
    //QString clientAddress = "192.168.1.247"; // Windows ***

    //QString clientAddress = "192.168.2.241"; // DebianVB

    bool connected = false;
    QHostAddress host;
    QByteArray datagram;

public slots:

    void startTransfer();
    void connectionEstablished();

private:


signals:

    void clientConnected();

};

#endif // CLIENT_H
