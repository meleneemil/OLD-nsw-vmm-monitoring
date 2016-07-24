#include "testsharedmem.h"

#include <iostream>
#include <vector>
#include <string>

#include <QtWidgets>
#include <QtNetwork>
#include <stdlib.h>
#include <QLocalServer>
#include <QLocalSocket>
#include <qlocalserver.h>
#include <qlocalsocket.h>

int waiting_time = 10000;

testSharedMemTool::testSharedMemTool() :
    previous_size(0),
    n_event_counter(0)
{
}

void testSharedMemTool::initializeSharedMemory()
{
    QLocalServer::removeServer("vmm-mon-server");
    server = new QLocalServer();
    if (!server->listen("vmm-mon-server"))
        qDebug() << "SERVER COM PROBLEM\n";
    else
        qDebug() << "NO PROBLEM\n";
}

void testSharedMemTool::sendData()
{
qDebug()<< "LETS SEND";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    qDebug()<< "LETS 1";
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << "MESSAGE TO SEND";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    qDebug()<< "LETS 2";
    QLocalSocket *clientConnection = server->nextPendingConnection();
    //TODO: add this connect?
    //        connect(clientConnection, SIGNAL(disconnected()),
    //                clientConnection, SLOT(deleteLater()));

    qDebug()<< "LETS 3";
    clientConnection->write(block);
    qDebug()<< "LETS 4";
    clientConnection->flush();
    qDebug()<< "LETS 5";
    clientConnection->disconnectFromServer();
    qDebug()<< "LETS 6";
}
