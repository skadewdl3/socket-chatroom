#ifndef SOCKETCHATROOM_SOCKETS_H
#define SOCKETCHATROOM_SOCKETS_H
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <exception>

#define INTERNET AF_INET

namespace sockets {

    enum socket_type {
        STREAM = SOCK_STREAM,
        DATAGRAM = SOCK_DGRAM,
        RAW = SOCK_RAW,
        RDM = SOCK_RDM,
        SEQPACKET = SOCK_SEQPACKET
    };

    enum socket_family {
        IPV4 = AF_INET,
        IPV6 = AF_INET6,
        UNIX = AF_UNIX,
        BLUETOOTH = AF_BLUETOOTH
    };

    enum socket_protocol {
        TCP = IPPROTO_TCP,
        UDP = IPPROTO_UDP,
        SCTP = IPPROTO_SCTP,
        DCCP = IPPROTO_DCCP,
        AUTO = 0,
        UDPLITE = IPPROTO_UDPLITE
    };

    class socket_address {
    private:
        sockaddr_in addr_data;
    public:
        int port;
        explicit socket_address (int);
        socket_address ();
        socket_address (int, socket_family);
        sockaddr_in get_addr_data();
    };

    class socket {
    private:
        socket_family family;
        socket_protocol protocol;
        socket_type type;
        int max_pending_connections = 5;
        socket_address address;

    public:
        int socket_fd; // move this to provate later
        explicit socket (socket_family, socket_type, socket_protocol);

        void send (std::string);

        void send (char*);

        void add_address ();

        std::string receive();
        std::string receive_loop();
    };

}

#endif //SOCKETCHATROOM_SOCKETS_H