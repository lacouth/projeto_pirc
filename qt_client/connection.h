#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include "../common/enums.h"

class Connection : public QObject
{
    Q_OBJECT
    QTcpSocket *tcpSocket = nullptr;
    QDataStream out;

public:
    Connection(QObject *parent = nullptr);
    void dataReceived();
    Q_INVOKABLE void conectarServidor(QString server_add, QString port);
};

#endif // CONNECTION_H
