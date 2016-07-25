
#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

class QLabel;
class QPushButton;
class QLocalServer;

class Server : public QDialog
{
    Q_OBJECT

public:
    Server(QString);

public slots:
    void sendFortune();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QLocalServer *server;
    QStringList fortunes;
    int index;
};

#endif
