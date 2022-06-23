#!/bin/bash#

g++ main.cpp ./Socket/Socket.cpp ./WebServer/WebServer.cpp ./Request/request.cpp ./Response/response.cpp -o main -lpthread -std=c++17
./main