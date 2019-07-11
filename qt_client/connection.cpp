#include "connection.h"

Connection::Connection(QObject *parent): QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    out.setDevice(tcpSocket);
    connect(tcpSocket, &QIODevice::readyRead, this, &Connection::dataReceived);
    //connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &Connection::displayError);
}

void Connection::dataReceived()
{

}



void Connection::conectarServidor(QString server_add, QString port)
{
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(server_add),port.toUShort());
    out << TYPE::USER;
}
