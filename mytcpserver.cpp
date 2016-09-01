#include "mytcpserver.h"
#include <QHostAddress>

myTcpServer::myTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    ClientSocketList = new QMap<int,myClientSocket*>();
    ClientSocketList->clear ();
}

void myTcpServer::incomingConnection(qintptr socketDescriptor)
{
    //给新加入的客户端编号
    myClientSocket *client=new myClientSocket(socketDescriptor);
    client->setSocketDescriptor(socketDescriptor);
    //读取新加入客户端的数据
    connect(client,SIGNAL(ClientReadDataSignal(int,QString,int,QByteArray)),this,SLOT(serverReadDataSlot(int,QString,int,QByteArray)));
    //断开当前客户端
    connect(client,SIGNAL(ClientDisConnectSignal(int,QString,int)),this,SLOT(serverDisConnectSlot(int,QString,int)));
    //将新的连接添加到列表
    client->clientID = ClientSocketList->size ();
    ClientSocketList->insert(client->clientID,client);
    emit serverConnectSignal (client->clientID, client->peerAddress().toString(),client->peerPort());
}

void myTcpServer::serverReadDataSlot(int clientID,QString IP,int Port,QByteArray data)
{
    emit serverReadDataSignal (clientID,IP,Port,data);
}

void myTcpServer::serverDisConnectSlot(int clientID,QString IP,int Port)
{
      ClientSocketList->remove(clientID);//连接管理中移除断开连接的socket
}

//指定客户端连接发消息
void myTcpServer::serverSendDataSlot(int senderID,int recieverID)
{

    QByteArray data = ClientSocketList->value(senderID)->dataArray.data ();
     ClientSocketList->value (recieverID) ->write (data);
}
