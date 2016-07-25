#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "server.h"
#include <qlocalserver.h>
#include <qlocalsocket.h>

Server::Server(QString serverName)
{
    index = 0;
    server = new QLocalServer(this);
    if (!server->listen(serverName)) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server->errorString()));
        close();
        return;
    }

    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.");

    connect(server, SIGNAL(newConnection()), this, SLOT(sendFortune()));

}

void Server::sendFortune()
{
//    qDebug() << "REQUEST";
//    for(int i=0;i<100;i++)
//    {
//        qDebug() << "sending "<<index;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << QString::number(index);
        index++;

        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));

        QLocalSocket *clientConnection = server->nextPendingConnection();
        connect(clientConnection, SIGNAL(disconnected()),
                clientConnection, SLOT(deleteLater()));

        clientConnection->write(block);
        clientConnection->flush();
        clientConnection->disconnectFromServer();
//    }

}

