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

    Q_PROPERTY(QString connStatus READ connStatus WRITE setConnStatus NOTIFY connStatusChanged)

    QTcpSocket *tcpSocket = nullptr;
    QDataStream server;
    QString _connStatus;

public:

    Connection(QObject *parent = nullptr);
    void dataReceived();

    QString connStatus(){
        return _connStatus;
    }

    void setConnStatus(QString s){
        _connStatus = s;
    }

     Q_INVOKABLE void conectarServidor(QString server_add, QString port);
signals:
    void connStatusChanged();


};

#endif // CONNECTION_H
