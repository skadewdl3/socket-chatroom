#include <iostream>
#include "sockets.hpp"
#include "json.hpp"


int main() {
    std::string str = R"({"name": "Soham"})";
    auto parser = json::Parser(str);

    auto socket = sockets::Socket();
}
