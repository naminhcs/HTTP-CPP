#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_

#include <errno.h>
#include <sys/epoll.h>
#include <netinet/tcp.h>

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

#include "../ThreadPool/ThreadPool.h"
#include "../Shared/Constant.h"
#include "../Socket/Socket.h"
#include "../Request/request.h"
#include "../Response/response.h"

class WebServer
{
    private:
        struct epoll_event event, ev, events[MAX_CONCURRENT_CONNECTIONS + 9];
        int concurrent_connections;
        int epoll_fd;
        std::mutex lock_epoll;

    public:
        void OpenServer(int port);
};

#endif // _WEB_SERVER_H_