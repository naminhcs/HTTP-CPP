#include "./WebServer/WebServer.h"

int main() {
    WebServer server;
    server.OpenServer(MY_PORT);
    return 0;
}