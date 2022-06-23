#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

class Socket
{
    private:
        int socket_value;
        sockaddr_in address;
        int binding;

    public:
        Socket(int domain, int type, int protocol, int port);
        int get_binding();
        int get_socket_value();
        sockaddr_in get_address();
};

#endif // _SOCKET_H_