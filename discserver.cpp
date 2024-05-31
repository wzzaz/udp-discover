#include "discserver.h"
#include "discverify.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

DiscServer::DiscServer(int broadcastPort, int replyPort)
{
    m_broadcastPort = broadcastPort;
    socket = new QUdpSocket;
    socket->bind(QHostAddress::Any, replyPort);
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()), this, SLOT(sendtimer()));
    qDebug() << __FUNCTION__ << timer.isActive() << this;
}

DiscServer::~DiscServer()
{
    if (socket) {
        socket->abort();
        socket->deleteLater();
    }
}

void DiscServer::broadcast(int msec)
{
    qDebug() << __FUNCTION__ << timer.isActive() << this;
    if (timer.isActive()) {
        timer.stop();
    }
    timer.start(msec);
}

void DiscServer::stop()
{
    if (timer.isActive()) {
        timer.stop();
    }
}

void DiscServer::sendtimer()
{
    QByteArray datagram = BROADCAST_STR.toLatin1();
    socket->writeDatagram(datagram, QHostAddress::Broadcast, m_broadcastPort);
}

void DiscServer::socketReadyRead()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        if (datagram.startsWith(REPLY_STR.toLatin1())) {
            QHostAddress ip4addr = QHostAddress(sender.toIPv4Address());
            QRegularExpression regex("\\[(.*?)\\]");
            QRegularExpressionMatch match = regex.match(datagram);
            QString clientName;
            if (match.hasMatch()) {
                clientName = match.captured(1);
            }
            emit clientFind(clientName, ip4addr.toString());
            qDebug() << "Message from Client: " << clientName << ip4addr.toString() << senderPort;
        }
    }
}
