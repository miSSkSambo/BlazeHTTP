#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <unordered_map>
#include <functional>

class Router {
public:
    using Handler = std::function<std::string()>;

    void get(const std::string& path, Handler handler);
    std::string route(const std::string& path);

private:
    std::unordered_map<std::string, Handler> routes;
};

#endif
