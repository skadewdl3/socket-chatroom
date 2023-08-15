#include <iostream>
#include "sockets.hpp"
#include "json.hpp"

using namespace sockets;
using namespace std;

void callback (sockets::socket sock, sockets::master_socket master) {
    cout << "This ran" << endl;
    cout << sock.receive() << endl;
}

int main() {


    auto socket = sockets::master_socket(socket_family::IPV4, socket_type::STREAM, socket_protocol::TCP);
    socket.set_port(8080);
    cout << socket.get_socket_fd() << endl;
    socket.bind();
    socket.listen();
    // auto client = socket.accept();
    // cout << client.receive() << endl;
    socket.accept_loop(callback);
    socket.close();
}
