#ifndef UDPDISCOVER_H
#define UDPDISCOVER_H

#ifndef DEFINE_HANDLE
    typedef void* HANDLE;
#define DEFINE_HANDLE
#endif

#ifndef DLL_EXPORT_API
#define DLL_EXPORT_API bool
#endif

#include <string>

typedef bool (*DISCOVER_FUNC)(std::string client_name, std::string ipaddr, void *user_ptr);

DLL_EXPORT_API udp_discover_server_init(HANDLE &handle, int boardcast_port, int reply_port, DISCOVER_FUNC discover_func, void *user_ptr);

DLL_EXPORT_API udp_discover_server_uninit(HANDLE &handle);

DLL_EXPORT_API udp_discover_server_boardcast(HANDLE handle, int send_interval);

DLL_EXPORT_API udp_discover_server_stop(HANDLE handle);


DLL_EXPORT_API udp_discover_client_init(HANDLE &handle, int boardcast_port, int reply_port, std::string client_name);

DLL_EXPORT_API udp_discover_client_uninit(HANDLE &handle);

#endif // UDPDISCOVER_H
