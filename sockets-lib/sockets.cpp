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

}

