//
//  mainwindow.cpp
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "frame.h"
#include "canvas.h"
#include "DetBase.h"
#include "DetDetector.h"
#include "daqclient.h"

#include "QTabWidget"
#include "QTimer"
#include <QLayout>
#include <QDebug>
#include <QAbstractButton>
//#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QIcon>

#include "TRandom.h"

using namespace online::display;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    panelLayout(0), loadFile(0), browseFile(0),
    buttonLayout(0), startButton(0), stopButton(0), pauseButton(0), configButton(0), settingsGeneral(0),
    mainTabs(), /*rawTabs(),*/ statisticsTabs(), rawChambers(), rawElectronics(), statisticsChambers(), statisticsElectronics(),
    EventDisplay(0), Statistics(0), StatisticsAdvanced(0), DaqStatistics(0),
    mainTreeWidget(0), SrsTree(0), chamberTree(0),
    rawFrame(), eventDisplayFrame_rawChambers(), chipsFrame_rawElectronics(),
    beamProfileFrame_statisticsChambers(), chargeFrame_statisticsChambers(), timeFrame_statisticsChambers(),chipsFrame_statisticsElectronics()
{
    //GUI setup for the main window
    ui->setupUi(this);
    createConfigurationPanel();
    setUpStatusBar();


    QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTabCanvas(int index)
{

    if(frame* tempFrame = mainTabs->widget(index)->layout()->findChild<frame*>())
        tempFrame->getFrameCanvas()->update();
}


QString* MainWindow::getSelectedItem_slot(QAbstractButton* button)
{
    QString* selectedItem = new QString(button->text());
    qDebug()<<"Selected item : "<< button->text();
    return selectedItem;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//functions for setup of the main window GUI, constant
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//to be prepared for run control (CURRENTLY NOT WORKING)
QStatusBar* MainWindow::setUpStatusBar()
{
    ui->statusbar->setFixedHeight(30);
    ui->statusbar->setFixedWidth(300);

    QFont labelFont;
    labelFont.setPointSize(10);
    labelFont.setBold(true);

    eventCounterLabel = new QLabel(QString(" Event #  :  "));
    eventCounterLabel->setAlignment(Qt::AlignCenter);
//    eventCounterLabel->setMinimumSize(runNumberLabel->sizeHint());
    eventCounterLabel->setStyleSheet("border: 0px solid grey");
    eventCounterLabel->setFont(labelFont);

    eventCounterLabel_update = new QLabel(QString("..."));
    eventCounterLabel_update->setAlignment(Qt::AlignCenter);
//    eventCounterLabel_update->setMinimumSize(runNumberLabel->sizeHint());
    eventCounterLabel_update->setStyleSheet("border: 0px solid grey");
    eventCounterLabel_update->setFont(labelFont);

    ui->statusbar->addPermanentWidget(eventCounterLabel,1);
    ui->statusbar->addPermanentWidget(eventCounterLabel_update,1);

    ui->statusbar->setStyleSheet("border: 1px solid grey");

    return onlineDisplayStatusBar;
}

void MainWindow::setUpTabEnvironment()
{
    mainTabs = new QTabWidget();
    mainTabs->clear();

    tabLayout = new QVBoxLayout();

    mainTabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    EventDisplay = new QTabWidget();
    Statistics = new QTabWidget();

    Statistics->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainTabs->setCurrentIndex(1);

    tabLayout->addWidget(mainTabs);

    setUpFrameEnvironment();

}

void MainWindow::setUpTreeEnvironment()
{

    mainTreeWidget = new QTreeWidget();
    mainTreeWidget->setColumnCount(1);
    mainTreeWidget->setUpdatesEnabled(true);

    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(0,QString("Element Selection"));
    mainTreeWidget->setHeaderItem(headerItem);

    chamberTree = new QTreeWidgetItem(mainTreeWidget);
    //chamberTree->setFlags(chamberTree->flags()|Qt::ItemIsUserCheckable);
    chamberTree->setText(0,"Chamber Elements");
    //chamberTree->setCheckState(0, Qt::Checked);
    chamberTree->setExpanded(1);

}
void MainWindow::setUpFrameEnvironment()
{


    QWidget* eventDisplayFrameTab = new QWidget();
    eventDisplayFrameTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget* statisticsFrameTab = new QWidget();
    statisticsFrameTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    eventDisplayFrame = new frame(eventDisplayFrameTab);
    eventDisplayFrame->frameType ="Event Display";
    addFrameToTabWidget(mainTabs,eventDisplayFrameTab,eventDisplayFrame,"Event Display");
    statisticsFrame = new frame(statisticsFrameTab);
    statisticsFrame->frameType ="Statistics";
    addFrameToTabWidget(mainTabs,statisticsFrameTab,statisticsFrame,"Statistics");


}

QVBoxLayout* MainWindow::setUpRunControl()
{
    runSettingsLayout = new QHBoxLayout();
    runControlLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    startButton = new QPushButton("START",0);
    startButton->setIconSize(QSize(25,25));
    stopButton = new QPushButton("STOP",0);
    stopButton->setIconSize(QSize(25,25));
    pauseButton = new QPushButton(QIcon(QString("button_pause_icon.png")),"",0);
    configButton = new QPushButton(QIcon(QString("button_config_icon.png")),"",0);
    configButton->setIconSize(QSize(25,25));
    settingsGeneral = new QPushButton("Run Settings",0);

    startButton->setEnabled(1);
    stopButton->setEnabled(0);
    settingsGeneral->setEnabled(1);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    runControlLayout->addLayout(buttonLayout);
    runControlLayout->addWidget(settingsGeneral);

    return runControlLayout;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//functions for modification and control of the main window GUI and its elements, dynamic
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



void MainWindow::addFrameToTabWidget(QTabWidget *parentTab, QWidget *targetWidget, frame *frameForTab, const char* tabTitle)
{
    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(frameForTab->getFrameCanvas());   //add frame->canvas to tab (not frame) to be resizable
    targetWidget->setLayout(l);
    addTab(parentTab, targetWidget, tabTitle);
    frameForTab->show();

}

void MainWindow::addTab(QTabWidget *parentTab, QWidget *childWidget, const char* tabTitle)  {

    childWidget->setWindowTitle(tabTitle);
    parentTab->addTab(childWidget, tabTitle);
    childWidget->setUpdatesEnabled(true);
    childWidget->show();

}


void MainWindow::createConfigurationPanel()
{
    panelLayout = new QWidget();
    QVBoxLayout *configPanelLayout = new QVBoxLayout(panelLayout);
    QTextEdit *insertCommand = new QTextEdit(panelLayout);
    insertCommand->setGeometry(2,3,2,3);
    QPushButton *sendCommand = new QPushButton(panelLayout);
    sendCommand->setText("SEND");
    configPanelLayout->addWidget(insertCommand);
    configPanelLayout->addWidget(sendCommand);
}

void MainWindow::openConfigurationPanel_slot()
{
    //if(timer->isActive()) reset_slot();
    panelLayout->show();

}

//checking the number of chambers that are selected for displaying


int MainWindow::getElementsNumberOfCheckedChildren(QTreeWidgetItem* parentTreeWidget)
{
    int numberOfElementsDisplayed=0;
    for(int i=0; i<parentTreeWidget->childCount(); i++)
    {
        if((parentTreeWidget->child(i))->checkState(0) == 2)
            numberOfElementsDisplayed++;
    }
    return numberOfElementsDisplayed;
}

//checking the number of chips that are selected for displaying
//int MainWindow::getElementsNumberOfCheckedChambersApvChips(QTreeWidgetItem* parentTreeWidget)
//{
//    int numberOfElementsDisplayed=0;
//    for(int i=0; i<parentTreeWidget->parent()->childCount(); i++)
//    {   for(int iChip=0; iChip<(parentTreeWidget->parent()->child(i))->childCount();iChip++)    {
//            if((parentTreeWidget->parent()->child(i))->child(iChip)->text(0).contains("APV", Qt::CaseInsensitive)
//                    && (parentTreeWidget->parent()->child(i))->child(iChip)->checkState(0)==2)
//            {
//                numberOfElementsDisplayed++;
////                qDebug("CHECK STATE for %s ===  ===  2 ",(parentTreeWidget->parent()->child(i))->child(iChip)->text(0));
////                mem_stripData.push_back(QString::fromUtf8(stripData.at(i).c_str()));

//                //numberOfElementsDisplayed+=getElementsNumberOfCheckedChildren(parentTreeWidget->parent()->child(i));
//            }
//        }
//    }
//    qDebug("numberOfElementsDisplayed = %i",numberOfElementsDisplayed);
//    return numberOfElementsDisplayed;
//}
