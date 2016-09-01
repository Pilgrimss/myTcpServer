#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include "myclientsocket.h"
#include <QByteArray>
class myTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTcpServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void serverReadDataSignal(int clientID,QString IP,int Port,QByteArray data);
    void serverConnectSignal(int clientID,QString IP,int Port);
    void serverDisConnectSignal(int clientID,QString IP,int Port);
    
private slots:
    void serverReadDataSlot(int clientID,QString IP,int Port,QByteArray data);
    void serverDisConnectSlot(int clientID,QString IP,int Port);
    void serverSendDataSlot(int senderID, int recieverID);

private:
    //客户端列表
    QMap <int, myClientSocket *>* ClientSocketList;
};

#endif // MYTCPSERVER_H
