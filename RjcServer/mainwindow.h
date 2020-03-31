#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

#include "server.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbServer_clicked();

    void slotNewClient(QString);
    void slotNewChatMsg(QString,QString);

private:
    Ui::MainWindow *ui;

    server *tcpServer;
};
#endif // MAINWINDOW_H
