//#include "mainwindow.h"
#include <TROOT.h>
#include <TRint.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <QApplication>
#include <QProcess>
#include <string>
#include <iostream>

#include <QLocalServer>
#include <QLocalSocket>
#include <qlocalserver.h>
#include <qlocalsocket.h>

#include <QtNetwork>

#include "server.h"

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    QLocalServer::removeServer("vmm-mon-server");
    Server* server = new Server("vmm-mon-server");
qDebug()<<"Server running";
    return a.exec();
}
