#include "sockets.hpp"


using namespace std;
using namespace sockets;


string sockets::socket::receive() {
    char buffer[1000] = { 0 };
    int receive_status = ::recv(this->socket_fd, buffer, sizeof(buffer), 0);
    if (receive_status < 0) {
        cout << "Error in receving data" << endl;
    }
    else if (receive_status == 0) {
        cout << "Sender closed connection before data was received" << endl;
    }
    return string(buffer);
}

void sockets::socket::receive_loop() {
    cout << "Starting receiving loop" << endl;
}


