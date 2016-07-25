#include "ShmemReader.h"
#include "SrsChipId.h"
#include <iostream>
#include <stdexcept>
using namespace online::display;

ShmemReader::ShmemReader(
        std::vector<std::pair<boost::shared_ptr<online::display::CDetChamber>,
        std::vector<boost::shared_ptr<online::display::CDetReadout> > > > chamberElements,
        MainWindow *window) :
    mainWindow(window), mainDrawer(0),
    configuredChamberElements(chamberElements), stripDataEvent(0), realEvent(false)
{
    eventCounter = 0;

    socket = new QLocalSocket();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
            this, SLOT(displayError(QLocalSocket::LocalSocketError)));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(connectToServer()));

    eventDisplayed = 0;
    mainDrawer = new DisplayDrawer(mainWindow);

    qRegisterMetaType< QString >("QVector<int>");
    qRegisterMetaType< QVector<int> >("QVector<int>");
    qRegisterMetaType< QVector<QString> >("QVector<QString>");
    qRegisterMetaType< QVector<std::pair<QString, QVector<int> > > >("QVector<std::pair<QString, QVector<int> > >");

    connect(this, SIGNAL(fillHistograms(std::vector<QString>,int)),
            mainDrawer,SLOT(NotifyFill(std::vector<QString>,int)),Qt::DirectConnection);
    connect(this, SIGNAL(drawHistograms()),
            mainDrawer,SLOT(NotifyDraw()),Qt::DirectConnection);

    startRequests();
}

void ShmemReader::connectToServer()
{

    blockSize = 0;
    socket->abort();
    socket->connectToServer("vmm-mon-server");
}

void ShmemReader::readFortune()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
        {
            qDebug() << "no bytes available";
            return;
        }
        in >> blockSize;
    }

    if (in.atEnd())
        return;

    QString nextFortune;
    in >> nextFortune;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, SLOT(connectToServer()));
        return;
    }
    eventCounter++;
    qDebug() << nextFortune;
    std::vector<QString> eventVector;
    //IMPORTANT TODO: edit to accomodate for multi hit events...
    //this now assumes that each packet tha comes is an event.
    eventVector.push_back(nextFortune);
    emit fillHistograms(eventVector,eventCounter);
    emit drawHistograms();
}

void ShmemReader::startRequests()
{
    timer->start(1);
}

void ShmemReader::stopRequests()
{
    timer->stop();
}

void ShmemReader::displayError(QLocalSocket::LocalSocketError socketError)
{
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        qDebug() << "The host was not found. Please check the host name and port settings.";
        break;
    case QLocalSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct.";
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        qDebug() << "The following error occurred: %1." <<  (socket->errorString());
    }
}

ShmemReader::~ShmemReader()
{
//    stopRequests();
    //    delete client;
    //    service->stopping(true);
    //    service->stop();
    delete timer;
    delete socket;
    delete mainDrawer;
    mainDrawer = 0;
}
