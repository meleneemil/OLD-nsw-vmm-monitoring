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

    index++;
    std::string str_strip = std::to_string(  (rand()%100)/2  +   (rand())%100/2    +120   );
    std::string str_charge = std::to_string(  (rand()%300)/4  +  (rand()%130)/4  +  (rand()%300)/4  +   (rand())%1500/4    +1000   );
    std::string str_time = std::to_string(  (rand()%500)/2  +   (rand())%500/2    +250   );
    std::string str_pdo = std::to_string(  (rand()%500)/2  +   (rand())%300/2    +100   );
    std::string str_tdo = std::to_string(  (rand()%150)/2  +   (rand())%350/2    +500   );

    std::string str_chamber="TZ2";
    //    if(rand()%2==0)
    //        str_chamber="TZ2";

    //      int n =  1    2             3 4 5   6           7 8  9    10             11          12           13
    std::string x =  " "+str_chamber+" 0 0 X "+str_strip+" 1 20 60 "+str_charge+" "+str_time+" "+str_pdo+" "+str_tdo;
QString msg = QString::number(index)+QString(QString::fromStdString(x));




//    qDebug() << "REQUEST";
//    for(int i=0;i<100;i++)
//    {
//        qDebug() << "sending "<<index;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << msg;

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
