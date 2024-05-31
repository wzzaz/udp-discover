#ifndef DISCCLIENT_H
#define DISCCLIENT_H

#include <QUdpSocket>
#include <QObject>

class DiscClient : public QObject
{
    Q_OBJECT
public:
    DiscClient(QString clientName, int broadcastPort = 12354, int replyPort = 12355);
    ~DiscClient();

private slots:
    void socketReadyRead();

private:
    void reply();

private:
    QUdpSocket *socket;
    int m_replyPort;
    QString m_clientName;
};

#endif // DISCCLIENT_H
