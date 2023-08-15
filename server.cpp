#include <iostream>
#include "sockets.hpp"
#include "json.hpp"

using namespace sockets;
using namespace std;

void callback (sockets::socket* sock, sockets::master_socket* master) {
    cout << sock->receive() << endl;
}

int main() {
    auto socket = sockets::master_socket(socket_family::IPV4, socket_type::STREAM, socket_protocol::TCP);
    socket.set_address("127.0.0.1");
    socket.set_port(3000);
    cout << socket.get_socket_fd() << endl;
    socket.bind();
    socket.listen();
    socket.accept_loop(callback);
    socket.close();
}
