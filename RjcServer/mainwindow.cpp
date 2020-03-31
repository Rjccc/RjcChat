#include "mainwindow.h"
#include "ui_mainwindow.h"

bool isServerStarted;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isServerStarted = false;

    tcpServer = new server();
    connect(tcpServer,SIGNAL(signalNewClient(QString)),SLOT(slotNewClient(QString)));
    connect(tcpServer,SIGNAL(signalNewChatMsg(QString,QString)),SLOT(slotNewChatMsg(QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbServer_clicked()
{
    if(isServerStarted){
        if(tcpServer->closeServer()){
            isServerStarted = false;
            ui->lIp->setText(tcpServer->server_ip);
            ui->lPort->setText(QString::number(tcpServer->server_port));
            ui->pbServer->setText("Start server");
        }
        return;
    }
    if(tcpServer->startServer()){
        isServerStarted = true;
        ui->lIp->setText(tcpServer->server_ip);
        ui->lPort->setText(QString::number(tcpServer->server_port));
        ui->pbServer->setText("Close server");
    }   else {
        isServerStarted = false;
        ui->lIp->setText(tcpServer->server_ip);
        ui->lPort->setText(QString::number(tcpServer->server_port));
        qDebug() << " its not working ";
    }
}

void MainWindow::slotNewClient(QString nameClient)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->twClients);
    item->setText(0,nameClient);
    item->setTextAlignment(0,Qt::AlignCenter);
    item->setText(1,"Connected");
    item->setTextAlignment(1,Qt::AlignCenter);
}

void MainWindow::slotNewChatMsg(QString name, QString msg){
    static int quItems = 0;
    quItems++;
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->twLog);
    item->setText(0,QString::number(quItems));
    item->setText(1,QTime::currentTime().toString());
    item->setText(2,name);
    item->setText(3,msg);
    for(int i = 0; i < ui->twLog->columnCount(); i++) item->setTextAlignment(i,Qt::AlignCenter);
}
