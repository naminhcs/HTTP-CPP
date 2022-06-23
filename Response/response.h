#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <iostream>
#include <vector>
#include <fstream>

#include "../Request/request.h"

const std::string HTTP_OK("HTTP/1.1 200 OK");
const std::string HTTP_NOT_FOUND("HTTP/1.1 404 NOT FOUND");

class Response {
    private:
        std::string response;

    public:
        Response(Request &req);
        std::string get_response();
};

#endif // _RESPONSE_H_
