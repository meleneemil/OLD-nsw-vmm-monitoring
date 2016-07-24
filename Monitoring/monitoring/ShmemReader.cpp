#include "ShmemReader.h"
#include "SrsChipId.h"
#include <QtWidgets>
#include <QtNetwork>
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
    //**********************
    socket = new QLocalSocket();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    blockSize = 0;
    socket->abort();
    socket->connectToServer("vmm-mon-server");
    if(socket->isOpen())
        qDebug() << "SOCKET IS OPEN";
    //**********************
    eventDisplayed = 0;
    mainDrawer = new DisplayDrawer(mainWindow);

    qRegisterMetaType< QString >("QVector<int>");
    qRegisterMetaType< QVector<int> >("QVector<int>");
    qRegisterMetaType< QVector<QString> >("QVector<QString>");
    qRegisterMetaType< QVector<std::pair<QString, QVector<int> > > >("QVector<std::pair<QString, QVector<int> > >");

    connect(this, SIGNAL(fillHistograms(std::vector<std::string>,int)),
            mainDrawer,SLOT(NotifyFill(std::vector<std::string>,int)),Qt::DirectConnection);
    connect(this, SIGNAL(drawHistograms()),
            mainDrawer,SLOT(NotifyDraw()),Qt::DirectConnection);
}

void ShmemReader::readFortune()
{
    qDebug() << "connectToServer";
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (in.atEnd()) return;

    QString nextFortune;
    in >> nextFortune;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, SLOT(requestNewFortune()));
        return;
    }

    currentFortune = nextFortune;

    qDebug() << nextFortune;
}

ShmemReader::~ShmemReader()
{
    socket->abort();
    //    service->stopping(true);
    //    service->stop();
    delete mainDrawer;
    mainDrawer = 0;
}
