#include "sockets.hpp"


using namespace std;
using namespace sockets;

void sockets::socket::send (string message) {
    cout << "Sending message: " << message << endl;
}

void sockets::socket::send (char* message) {
    this->send(std::string(message));
}