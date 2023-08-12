#include <iostream>
#include "sockets.hpp"
#include "json.hpp"

using namespace sockets;
using namespace std;

int main() {

    auto socket = sockets::socket(socket_family::IPV4, socket_type::STREAM, socket_protocol::TCP);

    cout << socket.socket_fd << endl;

}
