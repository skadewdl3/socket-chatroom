#include "sockets.hpp"


sockets::master_socket::master_socket (socket_family family, socket_type type, socket_protocol protocol) : socket(family, type, protocol) {
}

sockets::master_socket::master_socket (socket_family family, socket_type type, socket_protocol protocol, char* address) : socket(family, type, protocol, address) {
}

int sockets::master_socket::refresh_connections () {
    int max_fd = this->socket_fd;
    FD_SET(this->socket_fd, &this->fds);
    for (socket sock : this->connections) {
        FD_SET(sock.get_socket_fd(), &this->fds);
        if (sock.get_socket_fd() > max_fd) max_fd = sock.get_socket_fd();
    }
    return max_fd;
}

sockets::socket sockets::master_socket::accept() {
    socklen_t length = sizeof(this->address);
    int new_socket_fd = ::accept(this->socket_fd, (sockaddr*)&this->address, &length);
    if (new_socket_fd < 0) {
        cout << "Error in accepting connection" << endl;
    }
    socket new_socket = sockets::socket(this->family, this->type, this->protocol);
    new_socket.close();
    new_socket.set_socket_fd(new_socket_fd);
    this->connections.push_back(new_socket);
    for (socket sock : this->connections) {
        cout << sock.get_socket_fd() << " ";
    }
    cout << endl;
    this->refresh_connections();
    return this->connections[this->connections.size() - 1];
}

void sockets::master_socket::accept_loop(sockets::accept_loop_callback callback) {
    this->should_accept = true;
    while (this->should_accept) {
        int max_fd = this->refresh_connections();
        int activity = ::select(max_fd + 1, &this->fds, NULL, NULL, NULL);
        if (activity < 0) {
            cout << "Error while selecting socket" << endl;
        }

        if (FD_ISSET(this->socket_fd, &this->fds)) {
            this->accept();
            max_fd = this->refresh_connections();
        }

        for (int i = 0; i < this->connections.size(); i++) {
            socket sock = this->connections[i];
            if (FD_ISSET(sock.get_socket_fd(), &this->fds)) {
                callback(&sock, this);
            }
            if (sock.status() <= 0) {
                sock.close();
                this->connections.erase(this->connections.begin() + i);
            }
        }
    }
}

void sockets::master_socket::stop_accepting() {
    this->should_accept = false;
}

