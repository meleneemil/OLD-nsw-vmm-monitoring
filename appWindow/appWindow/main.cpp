#include "mainwindow.h"
#include <TROOT.h>
#include <TRint.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <QApplication>
#include <QProcess>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
