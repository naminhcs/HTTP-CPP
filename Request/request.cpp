#include "request.h"

Request::Request(const std::string &req) {
    size_t start_pos = 0;
    size_t end_pos = req.find(' ');

    // get method
    method = req.substr(start_pos, end_pos);
    start_pos = end_pos + 1;
    end_pos = req.find(' ', start_pos);

    // get url
    url = req.substr(start_pos, end_pos - start_pos);
}

std::string Request::get_method() {
    return method;
}

std::string Request::get_url() {
    return url;
}
