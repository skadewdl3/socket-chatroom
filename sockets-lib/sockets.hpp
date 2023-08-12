#ifndef SOCKETCHATROOM_SOCKETS_H
#define SOCKETCHATROOM_SOCKETS_H

namespace sockets {
    class Socket {
    private:
        int socket_fd;
    public:
        explicit Socket ();
        ~Socket ();
    };
}

#endif //SOCKETCHATROOM_SOCKETS_H