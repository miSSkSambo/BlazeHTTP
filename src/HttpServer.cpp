#include "HttpServer.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fstream>
#include <sstream>

#define MAX_EVENTS 1024
#define BUFFER_SIZE 4096

void setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

HttpServer::HttpServer(int p) : port(p) {
    router.get("/", []() {
        return "Welcome to BlazeHTTP";
    });

    router.get("/status", []() {
        return "Server running";
    });
}

void HttpServer::setupSocket() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setNonBlocking(server_fd);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, SOMAXCONN);
}

std::string HttpServer::readFile(const std::string& path) {
    std::ifstream file("public" + path);
    if (!file) return "";

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string HttpServer::buildResponse(const std::string& body,
                                      const std::string& status,
                                      bool keepAlive) {
    std::stringstream response;
    response << "HTTP/1.1 " << status << "\r\n";
    response << "Content-Length: " << body.size() << "\r\n";
    response << "Content-Type: text/plain\r\n";
    if (keepAlive)
        response << "Connection: keep-alive\r\n";
    response << "\r\n";
    response << body;
    return response.str();
}

void HttpServer::handleClient(int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes = read(client_fd, buffer, BUFFER_SIZE);

    if (bytes <= 0) {
        close(client_fd);
        return;
    }

    std::string request(buffer, bytes);

    std::istringstream iss(request);
    std::string method, path;
    iss >> method >> path;

    bool keepAlive = request.find("Connection: keep-alive") != std::string::npos;

    std::string body = router.route(path);

    if (body.empty())
        body = readFile(path);

    if (body.empty()) {
        body = "404 Not Found";
        std::string response = buildResponse(body, "404 Not Found");
        write(client_fd, response.c_str(), response.size());
        close(client_fd);
        return;
    }

    std::string response = buildResponse(body, "200 OK", keepAlive);
    write(client_fd, response.c_str(), response.size());

    if (!keepAlive)
        close(client_fd);
}

void HttpServer::start() {
    setupSocket();

    int epoll_fd = epoll_create1(0);

    epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event);

    epoll_event events[MAX_EVENTS];

    std::cout << "BlazeHTTP running on port " << port << "\n";

    while (true) {
        int count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < count; i++) {

            if (events[i].data.fd == server_fd) {

                int client_fd = accept(server_fd, nullptr, nullptr);
                setNonBlocking(client_fd);

                epoll_event client_event{};
                client_event.events = EPOLLIN;
                client_event.data.fd = client_fd;

                epoll_ctl(epoll_fd, EPOLL_CTL_ADD,
                          client_fd, &client_event);

            } else {
                handleClient(events[i].data.fd);
            }
        }
    }
}
