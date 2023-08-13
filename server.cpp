#include <iostream>
#include "sockets.hpp"
#include "json.hpp"

using namespace sockets;
using namespace std;

int main() {

    auto socket = sockets::socket(socket_family::IPV4, socket_type::STREAM, socket_protocol::TCP);
    socket.set_port(8080);
    cout << socket.get_socket_fd() << endl;
    socket.bind();
    socket.listen();
    auto client = socket.accept();

    string res = client.receive();
    cout << res << endl;

    socket.close();
}
