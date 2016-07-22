TEMPLATE = app


QT+= core gui
QT+=network
QT+=widgets
CONFIG += console
CONFIG+=c++11

boostinclude="/home/ak/boost_1_60_0/"
rootincludepath="/home/ak/ROOT534/include"

INCLUDEPATH += $$boostinclude
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
    EventBase.h \
    SrsTypes.h \
    SrsChip.h \
    SrsChipApv.h \
    SrsChipBnl.h \
    SrsChannelId.h \
    SrsChannel.h \
    SrsChannelData.h \
    SrsChipId.h \
    SrsEventId.h \
    SrsEventChannels.h \
    SrsFec.h \
    SrsBase.h \
    SrsNetworkDevice.h \
    SharedEBBuffer.h \
    SharedBufferHandler.h \
    SharedTypes.h \
    SharedChip.h \
    SharedChannel.h \
    SharedSrsChannelData.h \
    AsioService.h \
    ShmemReader.h \
    mmDaqSettingsWindow.h \
    mmDaqStartupWindow.h \
    DisplayDrawer.h

SOURCES += canvas.cxx main.cpp \
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
    EventBase.cpp \
    SrsChip.cpp \
    SrsChipApv.cpp \
    SrsChipBnl.cpp \
    SrsChipId.cpp \
    SrsChannelId.cpp \
    SrsChannel.cpp \
    SrsChannelData.cpp \
    SrsEventId.cpp \
    SrsEventChannels.cpp \
    SrsFec.cpp \
    SrsBase.cpp \
    SrsNetworkDevice.cpp \
    SharedEBBuffer.cpp \
    SharedBufferHandler.cpp \
    SharedChip.cpp \
    SharedChannel.cpp \
    SharedSrsChannelData.cpp \
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
