#include "Socket.h"

Socket::Socket(int domain, int type, int protocol, int port)
{
    socket_value = socket(domain, type, protocol);
    if (socket_value < 0) {
        perror("Error: Init socket");
        exit(EXIT_FAILURE);
    }
    int is_reuse = 1;
    if (setsockopt(socket_value, SOL_SOCKET, SO_REUSEADDR, &is_reuse, sizeof(int)) == -1){
        perror("Error: Set option euse address");
        exit(1);
    }
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    binding = bind(socket_value, (struct sockaddr *)&address, sizeof(address));
    if (binding < 0) {
        perror("Error: Binding socket");
        exit(EXIT_FAILURE);
    }
}

int Socket::get_binding() {
    return this->binding;
}
int Socket::get_socket_value() {
    return this->socket_value;
}
sockaddr_in Socket::get_address() {
    return this->address;
}
