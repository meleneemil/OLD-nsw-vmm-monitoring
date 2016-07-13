TEMPLATE = app


#+++++++++++++++++++++++++++++++
#Qmake configuration for linux
#+++++++++++++++++++++++++++++++

#win32 {
#   QMAKE_CXXFLAGS += -FIw32pragma.h
#}
#CONFIG += qt warn_on thread

QT+= core gui
QT+=network
QT+=widgets
CONFIG += console
CONFIG+=c++11

#boostinclude=../../Readout_Software/include/boost
boostinclude="/home/ak/boost_1_60_0/"
rootincludepath="/home/ak/ROOT534/include"

INCLUDEPATH += $$boostinclude
INCLUDEPATH += /opt/rh/devtoolset-1.1/root/usr/include
DEPENDPATH += $$boostinclude

INCLUDEPATH += $(ROOTSYS)/include
win32:LIBS += -L$(ROOTSYS)/lib -llibCint -llibRIO -llibNet \
        -llibHist -llibGraf -llibGraf3d -llibGpad -llibTree \
        -llibRint -llibPostscript -llibMatrix -llibPhysics \
        -llibGui -llibMathCore \
                -lRIO -lNet -lHist -lTree -lMatrix -lProof -lThread -lCore -lCint -lMathCore  -lTree -lm -ldl -rdynamic
else:LIBS += -L$(ROOTSYS)/lib -lCore -lCint -lRIO -lNet \
        -lHist -lGraf -lGraf3d -lGpad -lTree \
        -lRint -lPostscript -lMatrix -lPhysics \
        -lGui \ #-lMathCore \
        -lRIO -lNet -lHist -lTree -lMatrix -lProof -lThread -lCore -lCint -lMathCore  -lTree -lm -ldl  -rdynamic


LIBS += -L/home/ak/boost_1_60_0/stage/lib -lboost_program_options -lboost_thread -lboost_system -lboost_filesystem -lboost_date_time -lpthread -lrt

QMAKE_CXX_FLAGS += -std=c++11

HEADERS += canvas.h \
    #TQRootCanvas.h \
    #TQApplication.h \
    #TQCanvasImp.h \
    #TQCanvasMenu.h \
    #TQRootApplication.h \
    #TQRootDialog.h \
    #TQRootGuiFactory.h \
    frame.h \
    mainwindow.h \
    PropertyTreeParser.h \
    PropertyTreeParserDetector.h \
    PropertyTreeParserSrs.h \
    PropertyTreeParserChamber.h \
    DaqServerConfig.h \
    DetTypes.h \
    DetBase.h \
    DetChamber.h \
    DetConnector.h \
    DetDetector.h \
    DetLayer.h \
    DetMultiLayer.h \
    DetReadout.h \
    DetStripId.h \
    EventTypes.h \
    #eventhandler.h \
    EventBase.h \
    SrsTypes.h \
    SrsChip.h \
    SrsChipApv.h \
    SrsChipBnl.h \
    SrsChipMmDaqTest.h \
    #SrsChannelMmDaqTest.h \
    SrsChannelId.h \
    SrsChannel.h \
    SrsChannelData.h \
    SrsChipId.h \
    SrsEventId.h \
    SrsEventChannels.h \
    SrsFec.h \
#    SrsSru.h \
    SrsBase.h \
    SrsNetworkDevice.h \
    SRSEquipmentHeader.h \
    SharedEBBuffer.h \
    SharedBufferHandler.h \
    SharedTypes.h \
    SharedChip.h \
    SharedChannel.h \
    SharedSrsChannelData.h \
#    UDPFrame.h \
    Logger.h \
    pedestalsfileloader.h \
    #pedestals.h \
    #apv_raw_ped.h \
    filereader.h \
    AsioService.h \
    ShmemReader.h \
    mmDaqSettingsWindow.h \
    mmDaqStartupWindow.h \
    DisplayDrawer.h

SOURCES += canvas.cxx main.cpp \
    #TQRootCanvas.cxx \
    #TQApplication.cxx \
    #TQCanvasImp.cxx \
    #TQCanvasMenu.cxx \
    #TQRootApplication.cxx \
    #TQRootDialog.cxx \
    #TQRootGuiFactory.cxx \
    frame.cpp \
    mainwindow.cpp \
    PropertyTreeParser.cpp \
    PropertyTreeParserDetector.cpp \
    PropertyTreeParserSrs.cpp \
    PropertyTreeParserChamber.cpp \
    DaqServerConfig.cpp \
    DetBase.cpp \
    DetChamber.cpp \
    DetConnector.cpp \
    DetDetector.cpp \
    DetLayer.cpp \
    DetMultiLayer.cpp \
    DetReadout.cpp \
    DetStripId.cpp \
    #eventhandler.cpp \
    EventBase.cpp \
    SrsChip.cpp \
    SrsChipApv.cpp \
    SrsChipBnl.cpp \
    SrsChipMmDaqTest.cpp \
    #SrsChannelMmDaqTest.cpp \
    SrsChipId.cpp \
    SrsChannelId.cpp \
    SrsChannel.cpp \
    SrsChannelData.cpp \
    SrsEventId.cpp \
    SrsEventChannels.cpp \
    SrsFec.cpp \
#    SrsSru.cpp \
    SrsBase.cpp \
    SrsNetworkDevice.cpp \
    SRSEquipmentHeader.cpp \
    SharedEBBuffer.cpp \
    SharedBufferHandler.cpp \
    SharedChip.cpp \
    SharedChannel.cpp \
    SharedSrsChannelData.cpp \
#    UDPFrame.cpp \
    Logger.cpp \
    pedestalsfileloader.cpp \
    #pedestals.C \
    #apv_raw_ped.C \
    filereader.cpp \
    AsioService.cpp \
    ShmemReader.cpp \
    mmDaqSettingsWindow.cpp \
    mmDaqStartupWindow.cpp \
    DisplayDrawer.cpp

FORMS += \
    mainwindow.ui

RESOURCES += \

OTHER_FILES += \
    ../../../Desktop/DAQ-2000Series_simg_1.jpg \
    media/DAQ-2000Series_simg_1.jpg
