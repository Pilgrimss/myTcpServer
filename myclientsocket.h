#ifndef MYCLIENTSOCKET_H
#define MYCLIENTSOCKET_H

#include <QTcpSocket>
#include <QList>
class myClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit myClientSocket(qintptr socketDiscriptor, QObject *parent = 0);
    int clientID;

signals:
    void ClientReadDataSignal(int clientID,QString IP,int Port,QByteArray data);
    void ClientDisConnectSignal(int clientID,QString IP,int Port);

private slots:
    void ClientReadDataSlot();
    void ClientDisConnectSlot();


public:
    int senderID;
    int recieverID;
    QByteArray dataArray;
};

#endif // MYCLIENTSOCKET_H
