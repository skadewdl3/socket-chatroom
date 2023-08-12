#include "sockets.hpp"

using namespace std;
using namespace sockets;

sockets::socket_address::socket_address () {
    this->addr_data.sin_family = socket_family::IPV4;
    this->addr_data.sin_addr.s_addr = INADDR_ANY;
    this->addr_data.sin_port = htons(-1);
};

sockets::socket_address::socket_address (int port) {
    this->addr_data.sin_family = socket_family::IPV4;
    this->addr_data.sin_addr.s_addr = INADDR_ANY;
    this->addr_data.sin_port = htons(port);
};

sockets::socket_address::socket_address (int port, socket_family family) {
    this->addr_data.sin_family = family;
    this->addr_data.sin_addr.s_addr = INADDR_ANY;
    this->addr_data.sin_port = htons(port);
};

sockaddr_in sockets::socket_address::get_addr_data() {
    return this->addr_data;
}

void sockets::socket::set_family(sockets::socket_family new_family) {
    this->family = new_family;
    this->address = socket_address(this->address.port, this->family);
}

void sockets::socket::set_port(int port) {
    this->address = socket_address(port, this->family);
}
