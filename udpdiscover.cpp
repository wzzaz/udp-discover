#include "udpdiscover.h"
#include "discclient.h"
#include "discserver.h"

bool udp_discover_server_init(HANDLE &handle, int boardcast_port, int reply_port, DISCOVER_FUNC discover_func, void *user_ptr)
{
    DiscServer *server = new DiscServer(boardcast_port, reply_port);
    if (server) {
        QObject::connect(server, &DiscServer::clientFind, [discover_func, user_ptr](QString name, QString ipaddr){
            if (discover_func) {
                discover_func(name.toStdString(), ipaddr.toStdString(), user_ptr);
            }
        });

        handle = server;
        return true;
    }
    return false;
}

bool udp_discover_server_uninit(HANDLE &handle)
{
    if (handle) {
        DiscServer *server = (DiscServer*)handle;
        delete server;
        server = nullptr;
        handle = nullptr;
        return true;
    }
    return false;
}

bool udp_discover_server_boardcast(HANDLE handle, int send_interval)
{
    if (handle) {
        DiscServer *server = (DiscServer*)handle;
        qDebug() << __FUNCTION__ << server << handle;
        server->broadcast(send_interval);
        return true;
    }
    return false;
}

bool udp_discover_server_stop(HANDLE handle)
{
    if (handle) {
        DiscServer *server = (DiscServer*)handle;
        server->stop();
        return true;
    }
    return false;
}

bool udp_discover_client_init(HANDLE &handle, int boardcast_port, int reply_port, std::string client_name)
{
    DiscClient *client = new DiscClient(QString::fromStdString(client_name), boardcast_port, reply_port);
    if (client) {
        handle = client;
        return true;
    }
    return false;
}

bool udp_discover_client_uninit(HANDLE &handle)
{
    if (handle) {
        DiscClient *client = (DiscClient*)handle;
        delete client;
        client = nullptr;
        handle = nullptr;
        return true;
    }
    return false;
}
