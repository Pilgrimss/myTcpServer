#include "frmmain.h"
#include "ui_frmmain.h"
#include <QDebug>

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);   

    this->Init();
}

frmMain::~frmMain()
{
    delete ui;
}

//初始化
void frmMain::Init()
{
    ui->btnSend->setEnabled(false);
    ui->txtReceive->setReadOnly(true);
    server=new myTcpServer(this);
    connect(server,SIGNAL(serverConnectSignal(int,QString,int)),this,SLOT(frmMainConnect(int,QString,int)));
    connect(server,SIGNAL(serverDisConnectSignal(int,QString,int)),this,SLOT(frmMainDisConnect(int,QString,int)));
    connect(server,SIGNAL(serverReadDataSignal(int,QString,int,QByteArray)),this,SLOT(frmMainReadData(int,QString,int,QByteArray)));
    connect(this,SIGNAL(frmMainSendDataSignal(int,int)),server,SLOT(serverSendDataSlot(int,int)));
}

//读取来自某个客户端的信息
void frmMain::frmMainReadData(int clientID,QString IP,int Port,QByteArray data)
{    
    //如果数据不为空
    if (!data.isEmpty())
      ui->txtReceive->append(tr("Receive Data:%1 From:[clientID:%2 IP:%3 Port:%4]")
                                .arg(QString(data)).arg(clientID).arg(IP).arg(Port));
}

//显示上线信息
void frmMain::frmMainConnect(int clientID,QString IP,int Port)
{
    ui->txtReceive->append(tr("Client:[clientID:%1 IP:%2 Port:%3]Log In")
                           .arg(clientID).arg(IP).arg(Port));
    ui->cboxClient->addItem(tr("%1:%2:%3").arg(clientID).arg(IP).arg(Port));
}

//显示下线信息
void frmMain::frmMainDisConnect(int clientID,QString IP,int Port)
{
    ui->txtReceive->append(tr("Client:[clientID:%1 IP:%2 Port:%3] Log Out")
                           .arg(clientID).arg(IP).arg(Port));
    ui->cboxClient->removeItem(ui->cboxClient->findText(tr("%1:%2:%3").arg(clientID).arg(IP).arg(Port)));
}

//监听模式
void frmMain::on_btnListen_clicked()
{    
    if (ui->btnListen->text()==tr("Listen"))
    {
        bool ok=server->listen(QHostAddress::Any,ui->txtPort->text().toInt());
        if (ok)
        {
            ui->btnListen->setText(tr("Stop"));
            ui->txtReceive->append(tr("Listen Succeeded"));
            ui->btnSend->setEnabled(true);
        }
    }
    else
    {
        server->close();
        ui->btnListen->setText("Listen");
        ui->txtReceive->append("Listen Stoped");
        ui->btnSend->setEnabled(false);
    }
}

//传输数据
void frmMain::on_btnSend_clicked()
{    
    emit frmMainSendDataSignal(1,0);
    /*
    QString data=ui->txtSend->text();

    if (data==""){return;}

    int clientID = ;
    QString IP=str.split(":")[1];
    int Port=str.split(":")[2].toInt();
    //传输数据
   QByteArray clientData = this->server->ClientData[clientID];
        server->serverSendData(clientID,IP,Port,clientData);
    */
}

//清空显示
void frmMain::on_btnClear_clicked()
{
    ui->txtReceive->clear();
}
