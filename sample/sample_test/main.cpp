#include <QCoreApplication>
#include <QDebug>
#include "../../udpdiscover.h"
#include <string>

bool disc_cb(std::string client_name, std::string ipaddr, void *user_ptr) {
    qDebug() << __FUNCTION__ << QString::fromStdString(client_name);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HANDLE serverHd;
    udp_discover_server_init(serverHd, 12354, 12355, disc_cb, nullptr);
    udp_discover_server_boardcast(serverHd, 1000);

    HANDLE clientHd;
    udp_discover_client_init(clientHd, 12354, 12355, "M300-1001");


    return a.exec();
}
