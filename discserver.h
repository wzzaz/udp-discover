#ifndef DISCSERVER_H
#define DISCSERVER_H

#include <QUdpSocket>
#include <QObject>
#include <QTimer>

class DiscServer : public QObject
{
    Q_OBJECT
public:
    DiscServer(int broadcastPort = 12354, int replyPort = 12355);
    ~DiscServer();

    void broadcast(int msec = 1000);

    void stop();

signals:
    void clientFind(QString name, QString ipaddr);

private slots:
    void sendtimer();
    void socketReadyRead();

private:
    QUdpSocket *socket;

    QTimer timer;
    int m_broadcastPort;
};

#endif // DISCSERVER_H
