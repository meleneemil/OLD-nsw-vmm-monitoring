#include "testsharedmem.h"

#include <iostream>
#include <vector>
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

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
    m_shm_eventNumber(0),
    n_event_counter(0),
    m_shm_eventinfo_vector(0),
    m_shm_manager(0),
    m_shm_condition(0)
{
}


//// initialize the shared memory objects
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
    qDebug()<< "LETS 5";
    clientConnection->flush();
    qDebug()<< "LETS 6";
    clientConnection->disconnectFromServer();
    qDebug()<< "LETS 7";
}

void testSharedMemTool::sendEventNumber()
{
    *m_shm_eventNumber = n_event_counter;
    n_event_counter++;
}

void testSharedMemTool::sendEventInfo()
{
    std::string str_strip = std::to_string(  (rand()%100)/2  +   (rand())%100/2    +120   );
    std::string str_charge = std::to_string(  (rand()%300)/4  +  (rand()%130)/4  +  (rand()%300)/4  +   (rand())%1500/4    +1000   );
    std::string str_time = std::to_string(  (rand()%500)/2  +   (rand())%500/2    +250   );
    std::string str_pdo = std::to_string(  (rand()%500)/2  +   (rand())%300/2    +100   );
    std::string str_tdo = std::to_string(  (rand()%150)/2  +   (rand())%350/2    +500   );

    std::string str_chamber="TZ2";
    //    if(rand()%2==0)
    //        str_chamber="TZ2";

    //      int n =  1    2             3 4 5   6           7 8  9    10             11          12           13
    std::string x = "10 "+str_chamber+" 0 0 X "+str_strip+" 1 20 60 "+str_charge+" "+str_time+" "+str_pdo+" "+str_tdo;
    std::vector<std::string> out;
    for(int i = 0; i < 5; i++) {
        out.push_back(x);
    }
    ShmemCharString local_string(m_shm_manager->get_allocator<ShmemCharAllocator>());
    if(previous_size >= m_shm_eventinfo_vector->size())
        previous_size = m_shm_eventinfo_vector->size();

    if(m_shm_eventinfo_vector->size() > 200)
    {
        //don't send more to memory, because it fills it up, so we wait until the memory is read=cleared to send again.
        //maybe even clear the memory?
        m_shm_eventinfo_vector->clear();
    }
    else
    {
        for(auto ev : out) {
            local_string = ev.c_str();
            m_shm_eventinfo_vector->push_back(local_string);
        } // ev
    }
    out.clear();
    return;

}
