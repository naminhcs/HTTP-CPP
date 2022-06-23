#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <iostream>
#include <string.h>
#include <vector>
#include "../Shared/Constant.h"

class Request {
    private:
        std::string method;
        std::string url;

    public:
        Request(const std::string &req);
        std::string get_method();
        std::string get_url();
};
#endif // _REQUEST_H_
