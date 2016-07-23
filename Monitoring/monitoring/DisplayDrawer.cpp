//
//  DisplayDrawer.cpp
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#include "DisplayDrawer.h"
#include "SrsBase.h"
#include "SrsSru.h"
#include "SrsFec.h"
#include "SrsChannel.h"
#include "SrsChannelId.h"
#include "SrsChip.h"
#include "DetBase.h"
#include "DetDetector.h"
#include "DetConnector.h"
#include "DetReadout.h"
#include "DetChamber.h"

#include <QMetaType>


#ifndef Q_MOC_RUN
#include "DetBase.h"
#include "DetChamber.h"
#include "DetReadout.h"
#include "SrsTypes.h"
#include "DetTypes.h"
#include "SrsFec.h"
#include "SrsChip.h"
#include "ShmemReader.h"
#include "DisplayDrawer.h"
#endif

using namespace online::display;


int jjjj= 0;

DisplayDrawer::DisplayDrawer(
        MainWindow *mainWindow
        ) :
    service(new online::display::CAsioService(1)), monitoringMainWindow(), drawCondition(), drawMutex(),
    /*mem_rawData(0), */mem_stripData(0), mem_eventNumber(0), mem_eventNumber_str()
{
    online::display::CAsioService::MainLoopFunction f = boost::bind(&DisplayDrawer::drawSharedData, this);
    //    if(false)//aikoulou debug
    service->post(f);
    monitoringMainWindow = mainWindow;
    //aikoulou: comment outin. don't want to reset when stopping.
    connect(monitoringMainWindow,SIGNAL(stopDaqClicked()),this,SLOT(reset_slot()));
}


DisplayDrawer::~DisplayDrawer()
{
    service->stopping(true);
    service->stop();
}

void DisplayDrawer::NotifyFill(std::vector <std::string> stripData, int eventNumber)
{
    //aikoulou+ntekas: adjust to slot connection.
    mem_stripData.clear();
    for(int i=0;i<stripData.size();i++)
    {
        mem_stripData.push_back(QString::fromUtf8(stripData.at(i).c_str()));
    }

    mem_eventNumber = eventNumber;

    fillCondition.wakeOne();
}

void DisplayDrawer::NotifyDraw()
{
    drawCondition.wakeOne();
}

void DisplayDrawer::drawSharedData()
{
    while(!service->stopping()) {
        QMutexLocker locker(&drawMutex);
        if(fillCondition.wait(&drawMutex,1000))   {
            fillHistograms();
            mem_eventNumber_str.setNum(mem_eventNumber);
            monitoringMainWindow->eventCounterLabel_update->setText(mem_eventNumber_str);
            drawHistograms();
        }
        else    {
            continue;
        }
    }
}

void DisplayDrawer::changeActiveTab(int tabIndex)
{
    if(monitoringMainWindow->mainTabs->currentIndex()==0)   {
        drawEventHistos();
        //monitoringMainWindow->eventDisplayFrame->show();
    }
    else if(monitoringMainWindow->mainTabs->currentIndex()==1)  {
        drawStatisticsHistos();
    }
}

void DisplayDrawer::fillHistograms()
{
    readoutHistoFiller();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++Histogram Fillers+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void DisplayDrawer::readoutHistoFiller()
{
    if(!service->stopping())
        resetEventHistos_slot();//clearing event display histograms for new event
    for(int iLine = 0; iLine<mem_stripData.size(); iLine++)
    {
        handleBufferedEvent(mem_stripData.at(iLine));
    }
}



//Data buffer reader (SLOT)
int DisplayDrawer::handleBufferedEvent(QString line_qstr)
{
    std::string line_str = line_qstr.toStdString();
    int column=0;
    int processedEventNumber=-1000;
    CSrsChipId *currentChipId;
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ");
    tokenizer tokens(line_str, sep);
    tokenizer::iterator tok_iter = tokens.begin();

    //aikoulou: debug
    //containers for reading .bin file elements
    //elements' names
    std::string pinstr;
    std::string eventNumstr; //counter
    std::string channelstr;
    std::string chipstr;
    std::string fecstr; // 1 i 2
    std::string chiptypestr; //den xrismopieite
    std::string chamberstr; //chamber name from config
    std::string multilayerstr; //
    std::string layerstr;
    std::string readoutstr;
    std::string stripstr;
    //elements' data
    std::string chargestr; // 0- 2000 fortio
    std::string timestr;
    std::string chargeavgstr;
    std::string maxchargestr;

    std::string bcid_str;
    std::string extra_str;

    float charge=0;
    int time=0;
    int fec=0;
    int chip=0;
    int channel=0;

    column=0;
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        column++;
        pinstr = boost::trim_copy(*tok_iter);
        //std::cout<<pinstr<<std::endl;
        if(column == 1) {
            //std::cout<<"event # : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            eventNumstr = pinstr;
        }
        else if(column == 2) {
            //std::cout<<"chamber : "<<pinstr<<std::endl;
            chamberstr = pinstr;
        }
        else if(column == 3) {
            //std::cout<<"multilayer : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            multilayerstr = pinstr;
        }
        else if(column == 4) {
            //std::cout<<"layer : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            layerstr = pinstr;
        }
        else if(column == 5) {
            //std::cout<<"readout : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            readoutstr = pinstr;
        }
        else if(column == 6) {
            //std::cout<<"strip : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            stripstr = pinstr;
        }
        else if(column == 7) {
            //std::cout<<"fec : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            fecstr = pinstr;
        }
        else if(column == 8) {
            //std::cout<<"chip : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            chipstr = pinstr;
        }
        else if(column == 9) {
            //std::cout<<"channel : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            channelstr = pinstr;
        }
        else if(column == 10) {
            //std::cout<<"charge : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            chargestr = pinstr;
        }
        else if(column == 11) {
            //            std::cout<<"time : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            timestr = pinstr;
        }
        else if(column == 12) {
            //std::cout<<"charge : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            bcid_str = pinstr;
        }
        else if(column == 13) {
            //std::cout<<"charge : "<<pinstr<<std::endl;
            //getChannelReadout(pinstr);
            extra_str = pinstr;
        }
        else {
            std::cout<<"Data format not recognised..."<<std::endl;
            std::cout<< "column: " << column << std::endl;
        }
    }
    if(/*atoi(eventNumstr.c_str())==processedEventNumber ||*/ chamberstr=="unmapped")
    {return 0;}
    else {
        processedEventNumber == atoi(eventNumstr.c_str());
        //std::cout<<"got "<<chamberstr<<std::endl;
    }
    //currentChipId = new CSrsChipId(atoi(fecstr.c_str()),atoi(chipstr.c_str()));
    charge = atof(chargestr.c_str());
    time = atof(timestr.c_str());
    fec = atoi(fecstr.c_str());
    chip = atoi(chipstr.c_str());
    channel = atoi(channelstr.c_str());

    int bcid = atoi(bcid_str.c_str());
    int extra = atoi(extra_str.c_str());

//    int tdo=atof(tdo_str.c_str());
//    int pdo=atof(pdo_str.c_str());

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! use atof(strinf.c_str()) to convert string to double for filling values ion the histograms
    //std::cout<<"++++++++++++++++++++++++++++++++++++++++++Filling readout++++++++++++++++++++++++++++++++++++++++++++"<<std::endl;
    //++++++++++++++++++++++++filling readout histograms (accessing them from class objects)+++++++++++++++++++++
    fillReadoutHistos(chamberstr,readoutstr,atoi(stripstr.c_str()),charge,time, bcid,extra);
    return 1;

}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++Histogram Fillers+++++++++++++++++++++++++++++++++++++++++++++++++++++
//Get 1d/2d readout histogram to fill - Selecting from the histograms lists of each frame using a std::string
//histoType selection key

void DisplayDrawer::fillReadoutHistos(std::string chamberName, std::string readoutName, int strip, float charge, float time, int bcid, int extra)
{

    for(size_t i=0; i<monitoringMainWindow->chamberTree->childCount(); ++i)
    {

        QVariant chamberVar = monitoringMainWindow->chamberTree->child(i)->data(0,Qt::UserRole);
        CDetBase *chambptr = reinterpret_cast<CDetBase *>(chamberVar.value<void*>());
        if(chambptr->getMyChamberName()==chamberName)   {
            Q_FOREACH(DetBasePtr mlayervecptr,chambptr->get_children()) {
                Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                    Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {
                        boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                        if(readout->name()==readoutName)    {
                            readout->getStatisticsHisto()->Fill(strip);
                            readout->getTimeStatisticsHisto()->Fill(time);
                            readout->getChargeStatisticsHisto()->Fill(charge);
                            readout->getPDOStatisticsHisto()->Fill(bcid);
                            readout->getTDOStatisticsHisto()->Fill(extra);
                            //filling event display histograms
                            readout->getChargeEventHisto1d()->SetBinContent(strip,charge);
                            readout->getTimeEventHisto()->Fill(strip,time);
                            readout->getPDOEventHisto1d()->SetBinContent(strip,bcid);
                            readout->getTDOEventHisto1d()->SetBinContent(strip,extra);
                        }
                    }

                }
            }
        }
    }

}

void DisplayDrawer::fillChipHistos(int fecNumber, int chipNumber, int channelNumber, float charge, float time)
{
}


TH2D *DisplayDrawer::fillChip2dHisto(std::string chipName, std::string histoType)
{
    return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++Histogram drawers++++++++++++++++++++++++++++++++++++++++++++++
//draw histograms slot for displaying on active tab only
void DisplayDrawer::drawHistograms()
{
    if(monitoringMainWindow->mainTabs->currentIndex()==0)   {
        drawEventHistos();
        //        resetEventHistos_slot();
        //        monitoringMainWindow->eventDisplayFrame->frameCanvas->getCanvas()->Modified();
        //        monitoringMainWindow->eventDisplayFrame->frameCanvas->getCanvas()->Update();
    }
    else if(monitoringMainWindow->mainTabs->currentIndex()==1)   {
        drawStatisticsHistos();
    }
}

void DisplayDrawer::drawStatisticsHistos()
{
    int canvasIndex =1;
    for(size_t i=0; i<monitoringMainWindow->chamberTree->childCount(); ++i)
    {
        if(monitoringMainWindow->chamberTree->child(i)->checkState(0)==2)   {
            QVariant chamberVar = monitoringMainWindow->chamberTree->child(i)->data(0,Qt::UserRole);
            CDetBase *chambptr = reinterpret_cast<CDetBase *>(chamberVar.value<void*>());
            Q_FOREACH(DetBasePtr mlayervecptr,chambptr->get_children()) {
                Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                    Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {
                        boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                        monitoringMainWindow->statisticsFrame->draw1dHistogramInCanvas(readout->getStatisticsHisto(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->statisticsFrame->draw1dHistogramInCanvas(readout->getChargeStatisticsHisto(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->statisticsFrame->draw1dHistogramInCanvas(readout->getTimeStatisticsHisto(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->statisticsFrame->draw1dHistogramInCanvas(readout->getPDOStatisticsHisto(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->statisticsFrame->draw1dHistogramInCanvas(readout->getTDOStatisticsHisto(),canvasIndex);
                        canvasIndex++;
                    }

                }
            }
        }

    }
}


void DisplayDrawer::drawEventHistos()
{
    int canvasIndex =1;
    for(size_t i=0; i<monitoringMainWindow->chamberTree->childCount(); ++i)
    {
        if(monitoringMainWindow->chamberTree->child(i)->checkState(0)==2)   {
            QVariant chamberVar = monitoringMainWindow->chamberTree->child(i)->data(0,Qt::UserRole);
            CDetBase *chambptr = reinterpret_cast<CDetBase *>(chamberVar.value<void*>());
            Q_FOREACH(DetBasePtr mlayervecptr,chambptr->get_children()) {
                Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                    Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {
                        boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                        monitoringMainWindow->eventDisplayFrame->draw1dHistogramInCanvas(readout->getChargeEventHisto1d(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->eventDisplayFrame->draw2dHistogramInCanvas(readout->getTimeEventHisto(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->eventDisplayFrame->draw1dHistogramInCanvas(readout->getPDOEventHisto1d(),canvasIndex);
                        canvasIndex++;
                        monitoringMainWindow->eventDisplayFrame->draw1dHistogramInCanvas(readout->getTDOEventHisto1d(),canvasIndex);
                        canvasIndex++;
                    }

                }
            }
        }

    }
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++Histogram Reseters+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void DisplayDrawer::reset_slot()
{
    resetEventHistos_slot();
    //aikoulou: trying to make the plots resizable when stopped
    //    resetStatisticsHistos_slot();
}

void DisplayDrawer::resetStatisticsHistos_slot()
{
    for(size_t i=0; i<monitoringMainWindow->chamberTree->childCount(); ++i)
    {
        QVariant chamberVar = monitoringMainWindow->chamberTree->child(i)->data(0,Qt::UserRole);
        CDetBase *chambptr = reinterpret_cast<CDetBase *>(chamberVar.value<void*>());

        Q_FOREACH(DetBasePtr mlayervecptr,chambptr->get_children()) {
            Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {
                    boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                    readout->getStatisticsHisto()->Reset();
                    readout->getChargeStatisticsHisto()->Reset();
                    readout->getTimeStatisticsHisto()->Reset();
                    readout->getPDOStatisticsHisto()->Reset();
                    readout->getTDOStatisticsHisto()->Reset();
                }

            }
        }
    }
}

void DisplayDrawer::resetEventHistos_slot()
{
    for(size_t i=0; i<monitoringMainWindow->chamberTree->childCount(); ++i)
    {
        QVariant chamberVar = monitoringMainWindow->chamberTree->child(i)->data(0,Qt::UserRole);
        CDetBase *chambptr = reinterpret_cast<CDetBase *>(chamberVar.value<void*>());

        Q_FOREACH(DetBasePtr mlayervecptr,chambptr->get_children()) {
            Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {
                    boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                    readout->getChargeEventHisto1d()->Reset();
                    readout->getTimeEventHisto()->Reset();
                    readout->getPDOEventHisto1d()->Reset();
                    readout->getTDOEventHisto1d()->Reset();
                }

            }
        }
    }
}



