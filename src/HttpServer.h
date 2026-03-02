#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <string>
#include "Router.h"

class HttpServer {
public:
    HttpServer(int port);
    void start();

private:
    int port;
    int server_fd;
    Router router;

    void setupSocket();
    void handleClient(int client_fd);
    std::string buildResponse(const std::string& body,
                              const std::string& status = "200 OK",
                              bool keepAlive = false);
    std::string readFile(const std::string& path);
};

#endif
