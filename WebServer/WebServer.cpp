#include "WebServer.h"

void WebServer::OpenServer(int port)
{
    ThreadPool workers(MAX_WORKERS);

    Socket socket_id(AF_INET, SOCK_STREAM, INADDR_ANY, port);

    int listening = listen(socket_id.get_socket_value(), BACKLOG_MAX);

    // Create Epoll to listen file descriptor
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
		perror("Error: Create file descriptor epoll");
        exit(EXIT_FAILURE);
	}

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = socket_id.get_socket_value();
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_id.get_socket_value(), &event) == -1) {
        perror("Error: Regist event to epoll");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int event_count = epoll_wait(epoll_fd, events, MAX_CONCURRENT_CONNECTIONS + 1, 1000);
        for (int i = 0; i < event_count; ++i) {
            ev = events[i];
            
            // Handle connection is closing
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN))) {
                if ((epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev.data.fd, nullptr) == -1)) {
                    perror("Error: Delete event from epoll");
                    exit(EXIT_FAILURE);
                }
                close(ev.data.fd);
                continue;
            }

            if (ev.data.fd == socket_id.get_socket_value()) {
                // Handle when connection is coming
                sockaddr_in address = socket_id.get_address();
                int addrlen = sizeof(address);
                int conn_sock = accept(socket_id.get_socket_value(), (struct sockaddr *) &address, (socklen_t*)&addrlen);
                struct epoll_event temp;
                temp.events = EPOLLIN | EPOLLET;
                temp.data.fd = conn_sock;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_sock, &temp) == -1)
                {
                    perror("Error: In epoll_fd listening");
                    exit(EXIT_FAILURE);
                }
            } else {
                // handle request and response
                int socket_id = ev.data.fd;
                workers.EnQueue([socket_id] {
                    char buffer[MAX_LENGTH_BODY] = {0};
                    ssize_t valread = read( socket_id , buffer, MAX_LENGTH_BODY);
                    if (valread != 0 && valread != (ssize_t)(-1ll)) {
                        Request req(buffer);
                        Response res(req);
                        std::string res_str = res.get_response();
                        int status = write(socket_id, res_str.c_str(), res_str.length());
                    }
                    return 1;
                });
            }
        }
    }
}