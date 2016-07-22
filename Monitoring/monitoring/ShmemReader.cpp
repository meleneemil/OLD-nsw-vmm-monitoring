//
//  ShmemReader.cpp
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#include "ShmemReader.h"
#include "SrsChipId.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <stdexcept>

using namespace online::display;

namespace bpt = boost::property_tree;
//namespace bip = boost::interprocess;
namespace bptm = boost::posix_time;

int eventDisplayed_lastdisplayed=0;

//aikoulou: just trying to debug the code. will fake data.
bool FAKEDATA=false;
int FAKE_EVENT_NO=0;


ShmemReader::ShmemReader(
                         std::vector<std::pair<boost::shared_ptr<online::display::CDetChamber>,
                         std::vector<boost::shared_ptr<online::display::CDetReadout> > > > chamberElements,
                         MainWindow *window,
                         std::vector < std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH1D *> > > > mappingChip1dElements,
                         std::vector < std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH2D *> > > > mappingChip2dElements,
                         std::vector < std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH1D *> > > > mappingReadout1dElements,
                         std::vector < std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH2D *> > > > mappingReadout2dElements) :
    m_shm_shared_data(0), shmem(), shCond(), mainWindow(window), mainDrawer(0), service(new online::display::CAsioService(1)),
    m_shm_manager(bipc::open_only, "mmDaqSharedMemory") ,
    m_shm_condition(bipc::open_only, "mmDaqSharedCondition"), terminate(false),
    readMutex(), dataLine(),/* apvChipsList(), apvChipIdList(), */configuredChamberElements(chamberElements), isProcessing(false), stripDataEvent(0), rawEvent(0), realEvent(false)
{
    eventDisplayed = 0; // angelos
    if(m_shm_manager.check_sanity())    {
//        fillApvChipsList(apvList,apvChips);
        //        connect_shared_memory();		ANGELOS
        mainDrawer = new DisplayDrawer(mainWindow);

        qRegisterMetaType< QString >("QVector<int>");
        qRegisterMetaType< QVector<int> >("QVector<int>");
        qRegisterMetaType< QVector<QString> >("QVector<QString>");
        qRegisterMetaType< QVector<std::pair<QString, QVector<int> > > >("QVector<std::pair<QString, QVector<int> > >");

        //connectors for passing data from shared memory to local copies
        connect(this,SIGNAL(readEvent()),this,SLOT(read_event_number()));
        connect(this,SIGNAL(readRaw()),this,SLOT(read_raw_data()));
        connect(this,SIGNAL(readStrip()),this,SLOT(read_event_strips()));

        //connectors for controlling filling and drawing of the histograms from the displayDrawer
        connect(this,SIGNAL(runNumberIs(QString)),
                mainDrawer->monitoringMainWindow->runNumberLabel_update,SLOT(setText(QString)),Qt::QueuedConnection);

        connect(this, SIGNAL(fillHistograms(QVector<std::pair<QString,QVector<int> > >,std::vector<std::string>,int)),
                mainDrawer,SLOT(NotifyFill(QVector<std::pair<QString,QVector<int> > >,std::vector<std::string>,int)),Qt::DirectConnection);
        connect(this, SIGNAL(drawHistograms()),
                mainDrawer,SLOT(NotifyDraw()),Qt::DirectConnection);

        online::display::CAsioService::MainLoopFunction f = boost::bind(&ShmemReader::handleSharedData, this);
        service->post(f);
    }
    else
        std::cout<<"Shared Memory not found.../n mmDaq-server probably not running"<<std::endl;
}

ShmemReader::~ShmemReader()
{
    service->stopping(true);
    service->stop();
    delete mainDrawer;
    mainDrawer = 0;
}

void ShmemReader::connect_shared_memory()
{

    //connecting shared memory with daq
    try{
        boost::scoped_ptr<IpcShmemObjectType> obj(new
                                                  IpcShmemObjectType(bipc::open_only,
                                                                     "IPCPublisherSharedMemory" ,
                                                                     bipc::read_write));
        m_shm_object.swap(obj);


        //Map the whole shared memory in this process
        boost::scoped_ptr<IpcShmemMappedRegion> reg(new bipc::mapped_region(*m_shm_object,
                                                                            boost::interprocess::read_write ));

        m_shm_mapped_region.swap(reg);


        //Get the address of the mapped region
        void * addr = m_shm_mapped_region->get_address();

        //Construct the shared structure in memory
        m_shm_shared_data = static_cast<SPublisherIpcData*>(addr);

    }

    catch(...) {
        std::cout << "TODO : CShmemReader() connect_shared_memory() *** exception ***" << std::endl;
        m_shm_shared_data = 0;
    }

}

void ShmemReader::handleSharedData()
{

    ShmemNamedMutexType shm_mutex(bipc::open_only, "mmDaqSharedMutex");
    //aikoulou, from 5 to 1
    int time_ = 1;
    while(!service->stopping()) {
        {
            bptm::ptime timeout(bptm::second_clock::universal_time() + bptm::seconds(time_));
            ShmemNamedScopedLock lock(shm_mutex);
            if(m_shm_condition.timed_wait(lock, timeout)) {
                read_event_number();
                //aikoulou: try to unlock perhaps?
                std::cout << "Trying to unlock"<<std::endl;
                lock.unlock();
            }
            else {
                std::cout << "ShmemReader::handleSharedData    timeout from scoped lock" << std::endl;
                time_++;
                continue;
            }
        }

        if(realEvent && stripDataEvent.size()!=0) {
            emit fillHistograms(rawEvent, stripDataEvent, eventDisplayed);
            emit drawHistograms();
            //aikoulou 8-6-2016
            stripDataEvent.clear();
        }
    }//while


}

void ShmemReader::read_event_number()
{
    //Open managed shared memory
    std::pair<uint64_t*, size_t> res;
    qDebug(">>> read_event_number");
    res = m_shm_manager.find<uint64_t> ("mmDaqSharedEventNumber");


    //std::cout << "RES int = " << res.second << std::endl;
    //    qDebug(">>> going to grab event No");
    realEvent=false;
    if(res.second == 1)
    {
        //std::cout << "found : evid = " << *res.first << std::endl;
        //        qDebug(">>> Here is event number");
        if(eventDisplayed!=eventDisplayed_lastdisplayed)
        {
            std::cout << "eventDisplayed -->" << eventDisplayed << "<--" << std::endl;    //angelos
            eventDisplayed_lastdisplayed=eventDisplayed;
        }
        //            std::cout << "*res.first -->" << *res.first << "<--" << std::endl;

        if((((int)(*res.first))!=eventDisplayed) && (((int)(*res.first))!=0))   { //angelos
            eventDisplayed = *res.first;
            realEvent=true;
            std::cout<<"Trigger # : "<<(int)*res.first<<std::endl;
            //emit drawHistograms();
            //                read_raw_data(); //den xriazete

            read_event_strips();
            //emit newEventReceived(QString::number(*res.first));
            //emit drawHistograms();
        }
    }

}




void ShmemReader::read_event_strips()
{

    std::pair<ShmemCharStringVector*, size_t> res_str;
    res_str = m_shm_manager.find<ShmemCharStringVector> ("mmDaqSharedEventData");
    qDebug() << "void ShmemReader::read_event_strips RES vec = " << res_str.second;
    std::string line_str;
    if(res_str.second == 1)
    {
        stripDataEvent.clear();
        ShmemCharStringVector* vec = res_str.first;
        std::cout<<"Strip data vector size is "<<vec->size()<<std::endl;
        for (size_t ii = 0; ii < vec->size(); ++ii) {
            line_str = vec->at(ii).c_str();
            qDebug("DATA RCVD >>++++++++++++++++++++>>>");
            std::cout<<"+++++++++++"<<line_str<<"+++++++++++"<<std::endl;
            stripDataEvent.push_back(line_str);
            qDebug("DATA RCVD >>>+++++++++++++++++++>>");
        }
        vec->erase (vec->begin(), vec->end());

    }

    else {
        std::cout << "ERR: mmDaqSharedEventData resvec.second=" << res_str.second << std::endl;
    }
}



//read all chips from raw data segment
void ShmemReader::read_raw_data()
{
    std::pair<ShmemRawMap*, size_t>
            res = m_shm_manager.find< ShmemRawMap >( "mmDaqSharedRawData" ) ;

    int16_t rawValue;
    if (res.second != 1) {
        std::cout << "ERR: mmDaqSharedRawData resvec.second=" << res.second << std::endl;
    }
    ShmemRawMap::iterator it = res.first->begin();
    std::cout<<"Raw data vector size is "<<res.first->size()<<std::endl;
    for (; it != res.first->end(); ++it) {
        std::pair<QString, QVector< int > > rawData;
        std::string apvChipName;
        QVector<int> rawVector;
        apvChipName = getNameFromChipId(it->first);

        if(!apvChipName.empty()) {
            for(size_t ii = 0; ii < it->second.size(); ++ii)    {
                rawValue = static_cast<int16_t>(it->second.at(ii));
                rawVector.push_back(rawValue);
            }
        }
        if(rawVector.size()>1)  {
            rawData.first=QString(apvChipName.c_str());
            rawData.second=rawVector;
            rawEvent.push_back(rawData);
        }
    }

}

std::string ShmemReader::getNameFromChipId(uint32_t chipId)
{
    for(int iList=0; iList<apvChipsList.size(); ++iList)
    {
        if(apvChipIdList.at(iList)==chipId)
            return apvChipsList.at(iList);
    }
    return std::string();
}

