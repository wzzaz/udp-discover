#include <QCoreApplication>

#include "discclient.h"
#include "discserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DiscServer server;
    server.broadcast();

    DiscClient client("VS60-1001");

    return a.exec();
}
