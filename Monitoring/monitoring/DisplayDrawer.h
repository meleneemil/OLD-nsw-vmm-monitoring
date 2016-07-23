//
//  DisplayDrawer.h
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#ifndef DISPLAYDRAWER_H
#define DISPLAYDRAWER_H

#include "AsioService.h"
#include "mainwindow.h"
//#include "ShmemReader.h"
//#include "DaqServerConfig.h"

#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QTimer>
#include <QVector>

#include "TRandom.h"
#include "TH1.h"
#include "TH2.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>


//#include <QThread>
#ifndef Q_MOC_RUN

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#define BOOST_FILESYSTEM_NO_DEPRECATED
//#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_condition.hpp>


#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#endif

class DisplayDrawer : public QObject
{
    Q_OBJECT

public:
    DisplayDrawer(
        MainWindow *mainWindow
    );

    ~DisplayDrawer();

    online::display::CAsioService *service;
    MainWindow *monitoringMainWindow;

    QWaitCondition fillCondition;
    QWaitCondition drawCondition;
    QMutex drawMutex;

    int activeTabIndex;

    std::vector <QString> mem_stripData;
    int mem_eventNumber;
    QString mem_eventNumber_str;


public slots:

    //slots for manipulating thread
    void NotifyFill(std::vector <std::string> stripData, int eventNumber);
    void NotifyDraw();
    void drawSharedData();

    //slot to change active tab to be drawn

//    void changeActiveTab(int tabIndex);
    void readoutHistoFiller();
    int handleBufferedEvent(QString line_qstr);
    void fillReadoutHistos(std::string chamberName, std::string readoutName, int strip, float charge, float time, int pdo, int tdo);

    //drawers for each kind of the histogram
    void drawHistograms();
//    void updateCanvases();

    void drawStatisticsHistos();
    void drawEventHistos();


    void reset_slot();
    void resetStatisticsHistos_slot();
    void resetEventHistos_slot();

};

#endif // DISPLAYDRAWER_H
