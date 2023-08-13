#include "sockets.hpp"


using namespace std;
using namespace sockets;

void sockets::socket::send (string message) {
    this->send(message.c_str(), message.length());
}

void sockets::socket::send (char* message) {
    ::send(this->socket_fd, message, strlen(message), 0);
}


void sockets::socket::send (const char* message, size_t length) {
    ::send(this->socket_fd, message, length, 0);
}