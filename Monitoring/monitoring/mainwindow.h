//
//  mainwindow.h
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frame.h"
#include <QTabWidget>
#include <QTreeWidget>
#include <QTimer>
#include <QButtonGroup>
#include <QLayout>
#include <QLabel>
#include <QObject>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QList>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <TApplication.h>
#include <TSystem.h>

#ifndef Q_MOC_RUN
#endif

#include "TRandom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Ui::MainWindow *ui;
    ~MainWindow();

    TRandom *rndm;

    void addTab(QTabWidget *parentTab, QWidget *childWidget, const char* tabTitle);
    QStatusBar* setUpStatusBar();
    void setUpTabEnvironment();
    void setUpTreeEnvironment();
    void setUpFrameEnvironment();
    QVBoxLayout *setUpRunControl();

    int getElementsNumberOfCheckedChildren(QTreeWidgetItem* parentTreeWidget);

    QWidget *panelLayout;
    void addFrameToTabWidget(QTabWidget *parentTab, QWidget *targetWidget, frame *frameForTab, const char *tabTitle);
    void createConfigurationPanel();

    QStatusBar *onlineDisplayStatusBar;
    QLabel *runNumberLabel;
    QLabel *runNumberLabel_update;
    QLabel *eventCounterLabel;
    QLabel *eventCounterLabel_update;
    QLabel *mmDaqStatusLabel;
    QLabel *mmDaqStatusLabel_update;
    QLabel *statisticsLabel;
    QLabel *statisticsLabel_update;
    QLabel *commentDaqLabel;

    QHBoxLayout *runSettingsLayout;
    QVBoxLayout *runControlLayout;
    QHBoxLayout *buttonLayout;

    QGroupBox *runTypeGroupBox;

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *pauseButton;
    QPushButton *configButton;
    QPushButton *settingsGeneral;

    QVBoxLayout *tabLayout;
    QVBoxLayout *leftLayout;

    //tab widgets for graphics
    //main tab widget
    QTabWidget *mainTabs;

    //tree widgets for selecting different objects of each category
    QTreeWidget *mainTreeWidget;
    QTreeWidgetItem *SrsTree;
    QTreeWidgetItem *chamberTree;

    frame* eventDisplayFrame;
    frame* statisticsFrame;

    QString filename;

    QTimer* fRootTimer;
    QMainCanvas* testCanvas;

public slots:
    void updateTabCanvas(int index);
    void handle_root_events();

    virtual void fillStatistics() {}
    virtual void fillStatisticsHistos() {}
    virtual void reset_slot() {}
    virtual void handleBufferedEvent() {}
};

#endif // MAINWINDOW_H
