
#include "DaqServerConfig.h"
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
#include "frame.h"

#include <QObject>
#include <QTreeWidget>
#include "QTabWidget"
#include <QTimer>
#include <QLayout>
#include <QDebug>
#include <QAbstractButton>
//#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <QDir>
#include <QLineEdit>
#include <QThread>
#include <QMetaType>
#include <QString>

#include "TRandom.h"
#include "TH1D.h"
#include "TMath.h"

#include "mainwindow.h"
#include "mmDaqStartupWindow.h"
#include "PropertyTreeParserDetector.h"
#include "PropertyTreeParserChamber.h"
#include "PropertyTreeParserSrs.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
//#include <boost/foreach.hpp>
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
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>


#include <iostream>
#include <stdexcept>
#include <cstdlib> //std::system
//#include <cstddef>
//#include <cassert>
//#include <utility>

using namespace online::display;

namespace bpt = boost::property_tree;
namespace bip = boost::interprocess;
namespace bfs = boost::filesystem;
namespace bptm = boost::posix_time;


CDaqServerConfig::CDaqServerConfig() :
    mainWindow(),memReader(0), activeTabIndex(0), eventNumber(0), chamberElementsPairs(), chamberElements(), apvChipsList(),
    m_daq_cfg(),
    m_srs_cfg(),
    m_det_cfg(),
    m_daq_config_file(),
    m_srs_config_file(),
    m_det_config_file(),
    m_config_path(),
    m_srs_elements(),
    m_detector()

{

   mainStartUpWindow = new mmDaqStartupWindow(0);

   settingsWindow = new mmDaqSettingsWindow();
   settingsWindow->setUpdatesEnabled(true);
   settingsWindow->setWindowTitle("mmDaq Settings");

   qRegisterMetaType< std::string >("std::string");
   qRegisterMetaType< QString >("QString");
   qRegisterMetaType< std::vector<QString> >("std::vector<QString>");
//connect signals for configuration of the GUI and the DAQ

   //TODO REMOVE
//   connect(mainStartUpWindow,SIGNAL(configFileNameIs(QString)), this, SLOT(setConfigFileName(QString)));
   connect(mainStartUpWindow,SIGNAL(configFilePathIs(QString)), this, SLOT(setConfigFilePath(QString)));
   connect(settingsWindow,SIGNAL(reconfigFilePathIs(QString)),this,SLOT(setConfigFilePath(QString)));
   connect(this, SIGNAL(configWithFile(QString)),this,SLOT(configure(QString)));

   QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );
}

CDaqServerConfig::~CDaqServerConfig()
{
   delete mainWindow;
   mainWindow=0;
   delete memReader;
   memReader=0;
}


void CDaqServerConfig::clear()
{

   m_srs_cfg.clear();
   m_det_cfg.clear();

   m_srs_elements.clear();
   m_detector.reset();
}

void CDaqServerConfig::displayStartupWindow()
{
    mainStartUpWindow->setWindowTitle("Startup mmDaq GUI");
    mainStartUpWindow->setGeometry(500,400,250,100);
    mainStartUpWindow->show();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++Main Window Buttons Signal Transmitters+++++++++++++++++++++++++++++++++++++++++

void CDaqServerConfig::transmitStartSignal()
{

    try{
        memReader = new ShmemReader(chamberElements,mainWindow);

        qRegisterMetaType< QVector<int> >("QVector<int>");
        qRegisterMetaType< std::string >("std::string");

        mainWindow->stopButton->setEnabled(1);
        mainWindow->startButton->setEnabled(0);
//        mainWindow->saveCheckBox->setEnabled(0);
        mainWindow->settingsGeneral->setEnabled(0);
//        mainWindow->runTypeGroupBox->setEnabled(0);

    }
    catch (bip::interprocess_exception & e) {
        std::cout <<"************************************************************"<<std::endl;
        std::cout << "ShmemReader error : " << e.what() << " : mmDaqSharedMemory/mmDaqSharedCondition not found" << std::endl;
        std::cout <<"************************************************************"<<std::endl;
    }
    catch(...)
    {
        std::cout << "UNHANDLED Exception";
    };

}

void CDaqServerConfig::transmitStopSignal()
{

    //++++++++++++++++++++++++clearing reader and memory objects for cpu usage 0 on idle++++++++++++++++++
    std::cout<<"Terminating Mem Reading services"<<std::endl;

    memReader->mainDrawer->service->stopping(true);
    memReader->mainDrawer->service->stop();
    memReader->mainDrawer=0;

    memReader->service->stopping(true);
    memReader->service->stop();
    memReader=0;

    //button status change
    mainWindow->configButton->setEnabled(1);
    mainWindow->stopButton->setEnabled(0);
    mainWindow->startButton->setEnabled(1);
//    mainWindow->saveCheckBox->setEnabled(1);
    mainWindow->settingsGeneral->setEnabled(1);
//    mainWindow->runTypeGroupBox->setEnabled(1);


}

void CDaqServerConfig::openSettingsWindow()
{
    settingsWindow->show();
    settingsWindow->raise();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void CDaqServerConfig::setConfigFilePath(const QString &config_filePath)
{
    qDebug()<<"Got config File Path :"<<config_filePath;
    input_config_path = config_filePath;
    if(QFile::exists(input_config_path)) {
        emit configWithFile(config_filePath);
        mainStartUpWindow->close();
    }
}

void CDaqServerConfig::setConfigFileName(const QString &config_fileName)
{
    qDebug()<<"Got config File Name :"<<config_fileName;
    input_config_fileName = config_fileName;
}



//read configuration file
void CDaqServerConfig::configure(const QString &configFile)
{
    if(mainWindow!=NULL) {mainWindow->close(); mainWindow=NULL;}
    mainWindow = new MainWindow();
    mainWindow->setUpdatesEnabled(true);
    mainWindow->setWindowTitle("mmDaq GUI version\"still to go...\"");

    m_config_path = configFile.toStdString();
    std::cout<<configFile.toStdString()<<std::endl;


    m_config_path = configFile.toStdString();
    read_config_file(configFile.toStdString());

    configureTreeGui(mainWindow);

    connect(mainWindow->startButton, SIGNAL(clicked()), this, SLOT(transmitStartSignal()));
    connect(mainWindow->stopButton, SIGNAL(clicked()), this, SLOT(transmitStopSignal()));

    connect(mainWindow->settingsGeneral, SIGNAL(clicked()),this, SLOT(openSettingsWindow()));
    connect(mainWindow->mainTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(updateFrameCanvasesDivision_slot(QTreeWidgetItem*)));
    connect(mainWindow->mainTabs,SIGNAL(currentChanged(int)),mainWindow->mainTabs->currentWidget(),SLOT(show()));
    mainWindow->show();


}

void CDaqServerConfig::read_config_file(const std::string& filename)
{

   read_xml(filename, m_daq_cfg, boost::property_tree::xml_parser::trim_whitespace );


   m_srs_config_file = m_daq_cfg.get("daq_config.srs_file", "");
   m_det_config_file = m_daq_cfg.get("daq_config.detector_file", "");


   boost::filesystem::path daq_path(m_config_path);
   boost::filesystem::path srs_path(m_srs_config_file);
   boost::filesystem::path det_path(m_det_config_file);
   
   std::cout<<"daq path "<<daq_path<<std::endl;
   std::cout<<"srs path "<<srs_path<<std::endl;
   std::cout<<"det path "<<det_path<<std::endl;

   //make absolute paths for included config files
   if (!srs_path.has_parent_path()) {
      srs_path = daq_path.parent_path() / srs_path;
   }
   
   if (!det_path.has_parent_path()) {
      det_path = daq_path.parent_path() / det_path;
   }
   
   std::cout<<srs_path.string()<<std::endl;
   std::cout<<det_path.string()<<std::endl;

   read_srs_config_file(srs_path.string());
   read_detector_config_file(det_path.string());

}


void CDaqServerConfig::read_srs_config_file(const std::string& filename)
{

    m_srs_elements.clear();
   read_xml(filename, m_srs_cfg, boost::property_tree::xml_parser::trim_whitespace );
      
   try {
      CPropertyTreeParserSrs srsparser(m_srs_cfg, *this);
      std::vector<SrsBasePtr> elems = srsparser.make_srs_elements();
      m_srs_elements = elems;
   } catch (std::runtime_error &re) {
      std::cout << "Failed configuring srs:\n";
      std::cout << re.what() << std::endl;
   }

}


void CDaqServerConfig::read_detector_config_file(const std::string& filename)
{
    m_detector.reset();
   read_xml(filename, m_det_cfg, boost::property_tree::xml_parser::trim_whitespace );

   try {
      CPropertyTreeParserDetector detparser(m_det_cfg, *this);

      boost::shared_ptr<CDetBase> detptr = detparser.build_detector();
      m_detector = detptr;
   } catch (std::runtime_error &re) {
      std::cout << "Failed configuring detector:\n";
      std::cout << re.what() << std::endl;
   }

}

boost::filesystem::path CDaqServerConfig::get_config_path() const
{
      return m_config_path;
}

std::vector<boost::shared_ptr<CSrsChip> > CDaqServerConfig::locate_srs_chips() const {
   std::vector<boost::shared_ptr<CSrsChip> > vec;
   Q_FOREACH(SrsBasePtr sb, m_srs_elements) {
      boost::shared_ptr<CSrsFec> sf = boost::dynamic_pointer_cast<CSrsFec>(sb);
      if (sf ) {
         const std::vector<SrsChipPtr>& chips = sf->get_chips();
         vec.insert(vec.end(), chips.begin(), chips.end());
      }
   }
   return vec;
}


void CDaqServerConfig::configureTreeGui(MainWindow* window)
{
    std::cout<<"Configuring GUI according to SRS and Detector elements created according to config file"<<std::endl;

    mainWindow->setUpTabEnvironment();
    mainWindow->setUpTreeEnvironment();

        mainWindow->chamberTree->addChildren(buildChamberTreeGui(window));
        if(mainWindow->chamberTree==NULL) std::cout<<"chamber tree is a null pointer"<<std::endl;
        std::cout<<"====================================Chamber Elements Tree Ready======================================="<<std::endl;
        window->chamberTree->setExpanded(1);

        window->leftLayout = new QVBoxLayout();
        window->leftLayout->addWidget(mainWindow->mainTreeWidget);
        window->leftLayout->addLayout(mainWindow->setUpRunControl());
        window->leftLayout->setStretch(0,9);
        window->leftLayout->setStretch(1,1);

        window->ui->horizontalLayout->setSpacing(5);

        window->ui->horizontalLayout->addLayout(mainWindow->leftLayout);
        window->ui->horizontalLayout->addLayout(mainWindow->tabLayout);
        window->ui->horizontalLayout->setStretch(0,1);
        window->ui->horizontalLayout->setStretch(1,8);

}

//++++++++++++++++++++++++++++++++++++++Configuration of GUI's elements based on configuration file+++++++++++++++++++++++++++++++++++++++++

QList<QTreeWidgetItem*> CDaqServerConfig::buildChamberTreeGui(MainWindow *window)
{
    chamberElements.clear();
//    mappingChip1dElements.clear();
//    mappingChip2dElements.clear();
//    mappingReadout1dElements.clear();
//    mappingReadout2dElements.clear();

    //variables to fill the mapping list
    std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH1D *> > > mappingListElements1d;
    std::pair <std::vector<std::string>, std::vector <TH1D *> > mappingTreeElements1d;
    std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH2D *> > > mappingListElements2d;
    std::pair <std::vector<std::string>, std::vector <TH2D *> > mappingTreeElements2d;

    //QTreeWidgetItem* tempTreeWidgetItem = 0;

    //list with tree widget items for detector chamber
    QList<QTreeWidgetItem*> parentList;
    QList<QTreeWidgetItem*> childrenList;
    QList<QTreeWidgetItem*> grandChildrenList;
    QList<QTreeWidgetItem*> chambersList;
    QList<QTreeWidgetItem*> multiLayersList;
    QList<QTreeWidgetItem*> layersList;
    QList<QTreeWidgetItem*> readoutsList;

    size_t nOfReadouts = 0;
    Q_FOREACH(DetBasePtr chambvecptr, m_detector->get_children()) {
        mappingTreeElements1d.first.clear();
        mappingTreeElements2d.first.clear();
        multiLayersList.clear();
        chamberElementsPairs.first.reset();
        chamberElementsPairs.second.clear();

        chambersList.append(new QTreeWidgetItem(mainWindow->chamberTree, QStringList(QString(chambvecptr->name().c_str()))));
        qRegisterMetaType< DetBasePtrCont >("DetBasePtrCont");
        QVariant chamberVar = qVariantFromValue(reinterpret_cast<void*> (chambvecptr.get()));
        chambersList.last()->setData(0,Qt::UserRole,chamberVar);

        //append chambers chips under the chamber tree element
        chambersList.last()->insertChildren(0,classifyChips(locate_srs_chips(), chambersList.last(), chambvecptr,window));

        chambersList.last()->setExpanded(0);
        //connect(chambersList.last(),SIGNAL(emitDataChanged()),this,SLOT())
        mappingListElements1d.first = chambersList.last();
        mappingListElements2d.first = chambersList.last();

        //std::cout<<"teake care of the spare ones classification"<<std::endl;
        boost::shared_ptr<CDetChamber> chamber = boost::dynamic_pointer_cast<CDetChamber>(chambvecptr);
        chamberElementsPairs.first = chamber;
        Q_FOREACH(DetBasePtr mlayervecptr, chambvecptr->get_children()) {
            layersList.clear();
            //chambvecptr->

            multiLayersList.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(mlayervecptr->name().c_str()))));
            Q_FOREACH(DetBasePtr layervecptr, mlayervecptr->get_children()) {
                readoutsList.clear();
                layersList.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(layervecptr->name().c_str()))));

                //readoutVar.setValue(layervecptr->get_children());
                //chambersList.last()->setData(1, 0, readoutVar);
                Q_FOREACH(DetBasePtr baseptr, layervecptr->get_children()) {

                    mappingTreeElements1d.second.clear();
                    mappingTreeElements2d.second.clear();
                    readoutsList.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(baseptr->name().c_str()))));
                    //if(CDetReadout currentReadout = readoutvecptr-> lock())
                    boost::shared_ptr<CDetReadout> readout = boost::dynamic_pointer_cast<CDetReadout>(baseptr);
                    chamberElementsPairs.second.push_back(readout);
                    //std::cout<<dynamic_cast<CDetReadout*>(readoutvecptr)->getChargeEventHisto()->GetTitle()<<std::endl;
                    //static_cast<CDetReadout>(readoutvecptr).getChargeStatisticsHisto(); // Can now access, because we have a derived pointer

                    window->statisticsFrame->frameStatisticsHistos.push_back(readout->getStatisticsHisto());
                    window->statisticsFrame->frameStatisticsHistos.push_back(readout->getChargeStatisticsHisto());
                    window->statisticsFrame->frameStatisticsHistos.push_back(readout->getTimeStatisticsHisto());

                    //2d histos for evenet display
                    window->eventDisplayFrame->frameEventHistos.push_back(readout->getChargeEventHisto());
                    window->eventDisplayFrame->frameEventHistos.push_back(readout->getTimeEventHisto());

                    for(size_t i=0; i<readout->readout1dHistos.size(); ++i)
                    {
                        mappingTreeElements1d.first.push_back(readout->readout1dHistos.at(i)->GetName());
                        mappingTreeElements1d.second.push_back(readout->readout1dHistos.at(i));
                    }

                    for(size_t j=0; j<readout->readout2dHistos.size(); ++j)
                    {
                        mappingTreeElements2d.first.push_back(readout->readout2dHistos.at(j)->GetName());
                        mappingTreeElements2d.second.push_back(readout->readout2dHistos.at(j));
                    }

                    mappingListElements1d.second = mappingTreeElements1d;
                    mappingListElements2d.second = mappingTreeElements2d;

//                    mappingReadout1dElements.push_back(mappingListElements1d);
//                    mappingReadout2dElements.push_back(mappingListElements2d);

                    nOfReadouts++;
                }
            }
        }

        makeListItemsCheckable(readoutsList);
        chamberElements.push_back(chamberElementsPairs);
    }

    //chamber frame canvases setup
    divideFrameCanvases(nOfReadouts, window->statisticsFrame);
    divideFrameCanvases(nOfReadouts, window->eventDisplayFrame);

    //make list items checkable boxes
    makeListItemsCheckable(chambersList);
    std::cout<<"Number of Chambers : "<<chambersList.size()<<std::endl;
    std::cout<<"Number of readouts : "<<nOfReadouts<<std::endl;

    return chambersList;
}


//put chip elements under chamber elements (classification)
QList<QTreeWidgetItem*> CDaqServerConfig::classifyChips(std::vector<boost::shared_ptr<CSrsChip> > chipvec, QTreeWidgetItem* parentChamberElement, DetBasePtr chambvecptr, MainWindow *window)
{
    //variables to fill the mapping list
    std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH1D *> > > mappingListElements1d;
    std::pair <std::vector<std::string>, std::vector <TH1D *> > mappingTreeElements1d;
    std::pair < QTreeWidgetItem*, std::pair <std::vector<std::string>, std::vector <TH2D *> > > mappingListElements2d;
    std::pair <std::vector<std::string>, std::vector <TH2D *> > mappingTreeElements2d;
    QList<QTreeWidgetItem*> chamberChips;

    Q_FOREACH(boost::shared_ptr<CSrsChip> chipvecptr, chipvec)
    {
        mappingTreeElements1d.first.clear();
        mappingTreeElements2d.first.clear();
        mappingTreeElements1d.second.clear();
        mappingTreeElements2d.second.clear();

        if(chipvecptr->connector() !=0)  {
            if(DetBasePtr parentChamber = chipvecptr->connector()->parent().lock()) {
                if(QString(parentChamber->name().c_str()) == QString(chambvecptr->name().c_str()))  {

                    chamberChips.append(new QTreeWidgetItem(parentChamberElement, QStringList(QString(chipvecptr->name().c_str()))));
                    QVariant chipVar = qVariantFromValue(reinterpret_cast<void*> (chipvecptr.get()));
                    chamberChips.last()->setData(0,Qt::UserRole,chipVar);
/*
                    if(QString(chipvecptr->name().c_str()).contains("VMM2"))   {
                      bnlChipsList.push_back(chipvecptr->name());
                    }
*/
                    for(size_t i=0; i<chipvecptr->chip1dHistos.size(); ++i)
                    {
                        mappingTreeElements1d.first.push_back(chipvecptr->chip1dHistos.at(i)->GetName());
                        mappingTreeElements1d.second.push_back(chipvecptr->chip1dHistos.at(i));
                    }

                    for(size_t j=0; j<chipvecptr->chip2dHistos.size(); ++j)
                    {
                        mappingTreeElements2d.first.push_back(chipvecptr->chip2dHistos.at(j)->GetName());
                        mappingTreeElements2d.second.push_back(chipvecptr->chip2dHistos.at(j));
                    }

                    mappingListElements1d.first = chamberChips.last();
                    mappingListElements2d.first = chamberChips.last();

                    mappingListElements1d.second = mappingTreeElements1d;
                    mappingListElements2d.second = mappingTreeElements2d;

//                    mappingChip1dElements.push_back(mappingListElements1d);
//                    mappingChip2dElements.push_back(mappingListElements2d);
                }
            }
        }
    }
    makeListItemsCheckable(chamberChips);
    return chamberChips;
}


//function to make QList items checkable
void  CDaqServerConfig::makeListItemsCheckable(QList<QTreeWidgetItem*> list)
{
    for (int ilist = 0; ilist < list.length(); ++ilist) {
        list[ilist]->setFlags(list[ilist]->flags()|Qt::ItemIsUserCheckable);
        list[ilist]->setCheckState(0, Qt::Checked);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++GUI Histograms and canvases manipulation+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Update frame canvas division based on the selcted/deselected elements on the fly

void CDaqServerConfig::updateFrameCanvasesDivision_slot(QTreeWidgetItem* parentTreeItem)
{

    //aikoulou: let's try pausing monitoring here, and start again in the end of this function
    //in order to avoid crash during checking or unchecking.
//    qDebug("Pausing to avoid teh crash");
    usleep(100*1000);

    int numberOfReadoutElements;

    if(parentTreeItem->parent()->text(0) == "Chamber Elements") //changing canvas divisions for readout histos
    {
       selectDeselectChamberChildren(parentTreeItem);
       numberOfReadoutElements = numberOfReadoutsToDisplay(parentTreeItem->parent());
       divideFrameCanvases(numberOfReadoutElements,mainWindow->statisticsFrame);
       divideFrameCanvases(numberOfReadoutElements,mainWindow->eventDisplayFrame);

    }

    //aikoulou: let's try pausing monitoring here, and start again in the end of this function
    //in order to avoid crash during checking or unchecking.
    usleep(100*1000);
}

//frame canvas dividers based on frametype string
void CDaqServerConfig::divideFrameCanvases(int numberOfElements, frame* frameForDivide)
{
    int height=1;
    int width=1;

    if(frameForDivide->frameType == "Event Display")   {
        //aikoulou: plus two for pdo and tdo
        width=4;
//        width=2;
        height = numberOfElements;
    }
    else if(frameForDivide->frameType == "Statistics") {
        //aikoulou:
        width=5;
//        width=3;
        height = numberOfElements;
    }
    else if(frameForDivide->frameType == "Statistics Advanced") {
        width=3;
        height = numberOfElements;
    }
    else if(frameForDivide->frameType == "Apv Raw" || frameForDivide->frameType == "Chips Statistics")    {
        //width=4;
        if(numberOfElements<=width)  {
                width = numberOfElements;
                height=1;
        }
        else    {
            width = (int)TMath::Sqrt(numberOfElements);
            if(numberOfElements%width == 0)
                height = numberOfElements/width;
            else
                height = numberOfElements/width+1;
        }
    }


    else if(frameForDivide->frameType == "Daq Statistics") {
        width=3;

    }

    frameForDivide->divideCanvases(width,height);

}


//function to get on every chamber element selection change the number of readouts to be displayed
int CDaqServerConfig::numberOfReadoutsToDisplay(QTreeWidgetItem* parentTreeWidget)
{
    std::pair<boost::shared_ptr<CDetChamber>, std::vector<boost::shared_ptr<CDetReadout> > > chamberPairs;
    int numberOfReadoutsDisplayed=0;

    for(int i=0; i<parentTreeWidget->childCount(); i++)
    {
        if((parentTreeWidget->child(i))->checkState(0) == 2)    {
            for(size_t iChmb=0; iChmb<chamberElements.size(); iChmb++)
            {
                chamberPairs=chamberElements.at(iChmb);
                if(QString(chamberPairs.first->name().c_str())==(parentTreeWidget->child(i))->text(0))  {
                    //std::cout<<(parentTreeWidget->child(i))->text(0).toStdString()<<" "<<chamberPairs.first->name().c_str()<<" has "<<chamberPairs.second.size()<<std::endl;
                    numberOfReadoutsDisplayed+=chamberPairs.second.size();
                }
            }
        }
    }
    return numberOfReadoutsDisplayed;
}

void CDaqServerConfig::selectDeselectChamberChildren(QTreeWidgetItem* parentTreeWidget)
{
    for(int i=0; i<parentTreeWidget->childCount(); i++)
    {
        if(parentTreeWidget->checkState(0)==2)
            parentTreeWidget->child(i)->setCheckState(0,Qt::CheckState(2));
        else
            parentTreeWidget->child(i)->setCheckState(0,Qt::CheckState(0));
    }
}


