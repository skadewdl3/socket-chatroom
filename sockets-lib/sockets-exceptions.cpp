#include "sockets.hpp"

using namespace std;

template<typename... Args>
char* format_string(char* format, Args ...args) {
    int length = std::snprintf( nullptr, 0, format, args... );
    if (length < 0) return nullptr;

    char* buf = new char[length + 1];
    std::snprintf( buf, length + 1, format, args... );

    return buf;
}

char* sockets::exceptions::SocketException::get_message() {
    return this->message;
};

sockets::exceptions::SocketCreateException::SocketCreateException() {
    this->message = (char*)"Could not create socket";
};

sockets::exceptions::SocketBindException::SocketBindException(sockets::socket sock) {
    char* msg = (char*)"Could not bind socket to %s:%d";
    this->message = format_string(msg, sock.get_address(), sock.get_port());
};

sockets::exceptions::SocketListenException::SocketListenException() {
    this->message = (char*)"Could not listen on socket";
};

sockets::exceptions::SocketAcceptException::SocketAcceptException() {
    this->message = (char*)"Could not accept connection";
};

sockets::exceptions::SocketConnectException::SocketConnectException(sockets::socket sock) {
    char* msg = (char*)"Could not connect to %s:%d";
    this->message = format_string(msg, sock.get_address(), sock.get_port());
};

sockets::exceptions::SocketSendException::SocketSendException() {
    this->message = (char*)"Could not send message";
};

sockets::exceptions::SocketReceiveException::SocketReceiveException(sockets::socket sock) {
    char* message = (char*)"Could not receive message from socket %d.\nrecv status was: %d";
    this->message = format_string(message, sock.get_socket_fd(), sock.status());
};


sockets::exceptions::SocketSetOptionException::SocketSetOptionException() {
    this->message = (char*)"Could not set socket options";
}