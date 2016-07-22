//
//  mmDaqSettingsWindow.cpp
//  online_display
//
//  Created by Konstantinos Ntekas on 06/2012.
//  Copyright (c) 2012 CERN - PH/UAT. All rights reserved.
//


#include "mmDaqSettingsWindow.h"


mmDaqSettingsWindow::mmDaqSettingsWindow(QWidget *parent)
{
    settingWindowLayout = new  QVBoxLayout(this);

    fileSelectionLayout = new QHBoxLayout();
    fileSelectionLayout->addLayout(mmDaqSettingsWindow::setUpConfigFileSelection());

    settingWindowLayout->addLayout(fileSelectionLayout);
    settingWindowLayout->addLayout(setUpZeroSuppressionSettingsSelection());
}

//signal transmiters

void mmDaqSettingsWindow::transmitConfigFileNameSignal()
{
    qDebug()<<"transmiting config file signal";
    qDebug()<<configFileFullPath;

    //emit configFileNameIs(configFileName);
    emit reconfigFilePathIs(configFileFullPath);
}




QVBoxLayout* mmDaqSettingsWindow::setUpConfigFileSelection()
{
    QVBoxLayout* configLayout = new QVBoxLayout();
    configSectionLabel = new QLabel(QString("Configuration File Selection")) ;

    configFile = new QLineEdit("");
    configFile->setReadOnly(true);

    QHBoxLayout* configButtonsLayout = new QHBoxLayout();
    loadConfigFile = new QPushButton("Load Config");
    loadConfigFile->setEnabled(0);
    browseConfigFile = new QPushButton("Select Config");
    configButtonsLayout->addWidget(browseConfigFile);
    configButtonsLayout->addWidget(loadConfigFile);

    configLayout->addWidget(configSectionLabel);
    configLayout->addWidget(configFile);
    configLayout->addLayout(configButtonsLayout);

    connect(this->browseConfigFile,SIGNAL(clicked()),this,SLOT(searchForConfigFile()));
    connect(this->loadConfigFile,SIGNAL(clicked()),this,SLOT(transmitConfigFileNameSignal()));

    return configLayout;

}

QHBoxLayout* mmDaqSettingsWindow::setUpZeroSuppressionSettingsSelection()
{
    QHBoxLayout* varSettingsLayout = new QHBoxLayout();

    zeroSuppressionLabel = new QLabel(QString("Zero Suppression Factor")) ;
    zeroSuppressionBox = new QDoubleSpinBox(0);
    zeroSuppressionBox->setRange(0.0, 100.0);
    zeroSuppressionBox->setSingleStep(0.1);
    zeroSuppressionBox->setDecimals(1);
    zeroSuppressionBox->setValue(0.5);

    varSettingsLayout->addWidget(zeroSuppressionLabel);
    varSettingsLayout->addWidget(zeroSuppressionBox);

    return varSettingsLayout;

}

void mmDaqSettingsWindow::searchForConfigFile()
{
    //quint64 sizeOfFile=0;
    QDir *currentDir = new QDir(QDir::current());
    currentDir->cdUp();
    QString serverPath = currentDir->path();
    QString configPath = serverPath.append("/mmdaq3-server/config");
    configFileFullPath = QFileDialog::getOpenFileName(this,tr("Select Configuration File"),configPath,tr("Document files (*.xml)"),0);
    if(!configFileFullPath.isNull())   {
        QFileInfo pathInfo( configFileFullPath );
        configFileName = pathInfo.fileName();
    }
    configFile->setText(configFileName);
    loadConfigFile->setEnabled(1);
}

