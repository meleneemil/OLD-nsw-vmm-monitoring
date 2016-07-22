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
                         MainWindow *window) :
    mainWindow(window), mainDrawer(0), service(new online::display::CAsioService(1)),
    m_shm_manager(bipc::open_only, "mmDaqSharedMemory") ,
    m_shm_condition(bipc::open_only, "mmDaqSharedCondition"), terminate(false),
    configuredChamberElements(chamberElements), isProcessing(false), stripDataEvent(0), realEvent(false)
{
    eventDisplayed = 0;
    if(m_shm_manager.check_sanity())    {
        //        connect_shared_memory();		ANGELOS
        mainDrawer = new DisplayDrawer(mainWindow);

        qRegisterMetaType< QString >("QVector<int>");
        qRegisterMetaType< QVector<int> >("QVector<int>");
        qRegisterMetaType< QVector<QString> >("QVector<QString>");
        qRegisterMetaType< QVector<std::pair<QString, QVector<int> > > >("QVector<std::pair<QString, QVector<int> > >");

        //connectors for passing data from shared memory to local copies
        connect(this,SIGNAL(readEvent()),this,SLOT(read_event_number()));
        connect(this,SIGNAL(readStrip()),this,SLOT(read_event_strips()));

        //connectors for controlling filling and drawing of the histograms from the displayDrawer
        connect(this,SIGNAL(runNumberIs(QString)),
                mainDrawer->monitoringMainWindow->runNumberLabel_update,SLOT(setText(QString)),Qt::QueuedConnection);

        connect(this, SIGNAL(fillHistograms(std::vector<std::string>,int)),
                mainDrawer,SLOT(NotifyFill(std::vector<std::string>,int)),Qt::DirectConnection);
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


    }

    catch(...) {
        std::cout << "TODO : CShmemReader() connect_shared_memory() *** exception ***" << std::endl;
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
            emit fillHistograms(stripDataEvent, eventDisplayed);
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

    realEvent=false;
    if(res.second == 1)
    {
        if(eventDisplayed!=eventDisplayed_lastdisplayed)
        {
            std::cout << "eventDisplayed -->" << eventDisplayed << "<--" << std::endl;    //angelos
            eventDisplayed_lastdisplayed=eventDisplayed;
        }

        if((((int)(*res.first))!=eventDisplayed) && (((int)(*res.first))!=0))   { //angelos
            eventDisplayed = *res.first;
            realEvent=true;
            std::cout<<"Trigger # : "<<(int)*res.first<<std::endl;
            //emit drawHistograms();

            read_event_strips();
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




std::string ShmemReader::getNameFromChipId(uint32_t chipId)
{
    for(int iList=0; iList<apvChipsList.size(); ++iList)
    {
        if(apvChipIdList.at(iList)==chipId)
            return apvChipsList.at(iList);
    }
    return std::string();
}

