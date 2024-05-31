#include "discclient.h"
#include "discverify.h"
#include <QDebug>

DiscClient::DiscClient(QString clientName, int broadcastPort, int replyPort)
{
    m_clientName = clientName;
    m_replyPort = replyPort;
    socket = new QUdpSocket;
    socket->bind(QHostAddress::Any, broadcastPort);
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
}

DiscClient::~DiscClient()
{
    if (socket) {
        socket->abort();
        socket->deleteLater();
    }
}

void DiscClient::socketReadyRead()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if (datagram.compare(BROADCAST_STR.toLatin1()) == 0) {
            reply();
        }
    }
}

void DiscClient::reply()
{
    QByteArray datagram = QString("%1[%2]").arg(REPLY_STR).arg(m_clientName).toLatin1();
    socket->writeDatagram(datagram, QHostAddress::Broadcast, m_replyPort);
}
