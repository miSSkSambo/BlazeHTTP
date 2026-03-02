#include "Router.h"

void Router::get(const std::string& path, Handler handler) {
    routes[path] = handler;
}

std::string Router::route(const std::string& path) {
    if (routes.find(path) != routes.end())
        return routes[path]();
    return "";
}
