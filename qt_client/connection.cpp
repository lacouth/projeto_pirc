#include "connection.h"

Connection::Connection(QObject *parent): QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    server.setDevice(tcpSocket);

    connect(tcpSocket, &QIODevice::readyRead, this, &Connection::dataReceived);
    //connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &Connection::displayError);
}

void Connection::dataReceived()
{
    QString data = tcpSocket->readAll();

    qDebug() << data;

    tcpSocket->write(std::to_string(MESSAGE::GETDEVICES).c_str());
    tcpSocket->waitForBytesWritten();
}



void Connection::conectarServidor(QString server_add, QString port)
{
    tcpSocket->abort();

    do{
        tcpSocket->connectToHost(QHostAddress(server_add),port.toUShort(),QIODevice::ReadWrite);
    }while(!tcpSocket->isOpen());

    tcpSocket->write(std::to_string(TYPE::USER).c_str());
    tcpSocket->waitForBytesWritten();
    _connStatus = "Conectado";
}
