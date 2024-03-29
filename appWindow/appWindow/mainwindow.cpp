#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    sendData(0),
    m_testSharedMemTool(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sendData = new QPushButton("Send Data", this);
    sendData->move(10,10);
    sendData->show();

    m_testSharedMemTool = new testSharedMemTool();
    m_testSharedMemTool->initializeSharedMemory();

    connect(sendData, SIGNAL(clicked()), this, SLOT(sendDataToSharedMemory()));
}

void MainWindow::sendDataToSharedMemory()
{
    m_testSharedMemTool->sendData();
}

MainWindow::~MainWindow()
{
    boost::interprocess::shared_memory_object::remove("mmDaqSharedMemory");
    boost::interprocess::named_condition::remove("mmDaqSharedCondition");
    boost::interprocess::named_mutex::remove("mmDaqSharedMutex");

    delete ui;
}
