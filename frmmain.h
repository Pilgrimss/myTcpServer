#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "mytcpserver.h"

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();
signals:
    void frmMainSendDataSignal(int senderID, int recieverID);
private slots:

    void frmMainReadData(int clientID,QString IP,int Port,QByteArray data);
    void frmMainConnect(int clientID,QString IP,int Port);
    void frmMainDisConnect(int clientID,QString IP,int Port);
    void on_btnListen_clicked();
    void on_btnSend_clicked();
    void on_btnClear_clicked();

private:
    Ui::frmMain *ui;

    myTcpServer *server;

    void Init();

};

#endif // FRMMAIN_H
