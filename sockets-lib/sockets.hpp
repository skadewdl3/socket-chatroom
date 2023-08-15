#ifndef SOCKETCHATROOM_SOCKETS_H
#define SOCKETCHATROOM_SOCKETS_H
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <exception>
#include <cstring>
#include <vector>
#include <optional>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>

using namespace std;

namespace sockets {

    // Declarations of enums for type, family and protocol options
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

    // Forward declarations for classes
    class socket;
    class master_socket;

    // Function type passed to master_socket's
    // accept_loop method as a callback
    typedef void (*accept_loop_callback) (socket*, master_socket*);


    class socket {
    protected:
        socket_family family;
        socket_protocol protocol;
        socket_type type;
        int port;
        int max_pending_connections = 5;
        sockaddr_in address;
        int socket_fd; // move this to provate later


        void send (const char*, size_t);
        void refresh_socket ();

    public:
        socket (socket_family, socket_type, socket_protocol);
        socket (socket_family, socket_type, socket_protocol, char*);
        int status ();

        // Setters
        void set_family (socket_family);
        void set_port (int);
        void set_protocol (socket_protocol);
        void set_type (socket_type);
        void set_socket_fd (int);
        void set_address(char*);

        // Getters
        int get_socket_fd ();
        int get_port ();
        char* get_address ();

        // Common Functions
        void send (std::string);
        void send (char*);
        void close();
        string receive();

        // Server Functions
        void bind ();
        void listen();

        virtual socket accept();

        // Client Functions
        void connect ();

    };


    class master_socket : public socket {
    private:
        fd_set fds;
        vector<socket> connections;
        int refresh_connections();
        bool should_accept = true;
    public:
        master_socket (socket_family, socket_type, socket_protocol);
        master_socket (socket_family, socket_type, socket_protocol, char*);
        socket accept() override;
        void stop_accepting ();
        void accept_loop(accept_loop_callback);
    };

    namespace exceptions {
        class SocketException : std::exception {
        protected:
            char *message;
        public:
            char *get_message();
        };

        class SocketCreateException : SocketException {
        public: SocketCreateException();
        };

        class SocketBindException : SocketException {
        public: explicit SocketBindException(sockets::socket);
        };

        class SocketListenException : SocketException {
            public: SocketListenException();
        };

        class SocketAcceptException : SocketException {
            public: SocketAcceptException();
        };

        class SocketConnectException : SocketException {
        public: explicit SocketConnectException(sockets::socket);
        };

        class SocketSendException : SocketException {
            public: SocketSendException();
        };

        class SocketReceiveException : SocketException {
        public:  explicit SocketReceiveException(sockets::socket);
        };

        class SocketSetOptionException : SocketException {
            public: SocketSetOptionException();
        };
    }

}

#endif //SOCKETCHATROOM_SOCKETS_H