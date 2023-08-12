#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "sockets.hpp"

using namespace sockets;

sockets::Socket::Socket() {
    std::cout << "Creating socket" << std::endl;
}

sockets::Socket::~Socket() {
    std::cout << "Destroying socket" << std::endl;
}


