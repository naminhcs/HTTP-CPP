#include "response.h"

void ReadFile(const std::string &path, std::vector<char> &res) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    res.resize(size);
    if (!file.read(res.data(), size)) {
        perror("Error: Read file");
        exit(EXIT_FAILURE);
    }
    file.close();
}

int ProcessRequest(Request &req, std::vector<char> &res) {
    int status = 404;
    std::string file_dic("./Shared/");
    if (req.get_method() == "GET") {
        if (req.get_url() == "/favicon.ico") {
            status = 404;
        } else if (req.get_url() == "/") {
            status = 200;
            file_dic += "index.html";
        } else if (req.get_url() == "/show-image") {
            status = 200;
            file_dic += "img.html";
        } else if (req.get_url() == "/1.png") {
            status = 200;
            file_dic = "./Database/1.png";
        }
        if (status == 404) file_dic += "404.html";
        ReadFile(file_dic, res);
    }
    return status;
}

Response::Response(Request &req) {
    std::vector<char> body_response;
    int status = ProcessRequest(req, body_response);
    if (status == 200) {
        std::string type("image/png");
        std::string alive("close");
        if (req.get_url().find("/1.png") == std::string::npos) type = "text/html";
        response = HTTP_OK + "\r\n";
        response = response + "Connection: keep-alive\r\n";
        response = response + "Content-Type: " + type + "\r\n";
        response = response + "Content-Length: " + std::to_string(body_response.size()) + "\r\n";
        response = response + "\r\n" + std::string(body_response.begin(), body_response.end());
    } else {
        response = HTTP_NOT_FOUND + "\r\n";
        response = response + "Connection: keep-alive\r\n";
        response = response + "Content-Type: text/html\r\n";
        response = response + "Content-Length: " + std::to_string(body_response.size()) + "\r\n";
        response = response + "\r\n" + std::string(body_response.begin(), body_response.end());
    }
}

std::string Response::get_response() {
    return response;
}