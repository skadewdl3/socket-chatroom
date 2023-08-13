#include "sockets.hpp"

using namespace std;
using namespace sockets;


sockets::socket::socket(socket_family family, socket_type type, socket_protocol protocol) {
    std::cout << "Creating socket" << std::endl;
    this->family = family;
    this->type = type;
    this->protocol = protocol;

    // Create the socket
    this->socket_fd = ::socket(family, type, protocol);
    if (this->socket_fd < 1) cout << "Error in creating socket" << endl;
    // TODO: add try-catch block later

    this->address.sin_family = socket_family::IPV4;
    this->address.sin_addr.s_addr = INADDR_ANY;
    this->address.sin_port = htons(-1);
}

void sockets::socket::refresh_socket () {
    this->close();
    this->address.sin_family = this->family;
    this->address.sin_port = htons(this->port);
    this->socket_fd = ::socket(this->family, this->type, this->protocol);
}

void sockets::socket::set_family (socket_family new_family) {
    this->family = new_family;
    this->address.sin_family = new_family;
    this->refresh_socket();
}

void sockets::socket::set_protocol (socket_protocol new_protocol) {
    this->protocol = new_protocol;
    this->refresh_socket();
}

void sockets::socket::set_type (socket_type new_type) {
    this->type = new_type;
    this->refresh_socket();
}

int sockets::socket::get_socket_fd () {
    return this->socket_fd;
}

void sockets::socket::set_port (int new_port) {
    this->port = new_port;
    this->address.sin_port = htons(new_port);
}

void sockets::socket::set_socket_fd (int new_socket_fd) {
    this->socket_fd = new_socket_fd;
}

void sockets::socket::bind () {
    ::bind(this->socket_fd, (sockaddr*)&this->address, sizeof(this->address));
}

void sockets::socket::listen () {
    ::listen(this->socket_fd, this->max_pending_connections);
}

sockets::socket sockets::socket::accept () {
    socklen_t length = sizeof(this->address);
    int new_socket_fd = ::accept(this->socket_fd, (sockaddr*)&this->address, &length);
    if (new_socket_fd < 0) {
        cout << "Error in accepting connection" << endl;
    }
    socket new_socket = sockets::socket(this->family, this->type, this->protocol);
    new_socket.close();
    new_socket.set_socket_fd(new_socket_fd);
    return new_socket;
}

void sockets::socket::close () {
    ::close(this->socket_fd);
}
void sockets::socket::connect () {
    int connection_status = ::connect(this->socket_fd, (sockaddr*)&this->address, sizeof(this->address));
    if (connection_status < 0) {
        cout << "Error in connecting" << endl;
    }
}


