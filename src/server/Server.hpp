#ifndef SHDOCUMENT_SERVER_HPP
#define SHDOCUMENT_SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "../common/Common.hpp"
#include "../common/exception/Exception.hpp"

#define PORT 3000

namespace nakhoadl {
    using namespace Socket;
    class Server {
    private:
        SocketFileDescriptor socketFileDescriptor;

        /**
         * Server constructor
         */
        Server();

        /**
         * Server destructor
         */
        ~Server();

        /**
         * Static instance of class
         */
        static Server *instance;

        /**
         * Create socket
         *
         * @return `Server &'
         */
        Server &createSocket();

        /**
         * Bind socket
         *
         * @return `Server &'
         */
        Server &binding();

    public:
        /**
         * Get instance of class
         *
         * @return Server*
         */
        static Server *getInstance();

        /**
         * Socket start listen
         */
        void start();

        /**
         *
         */
        void close();
    };
}


#endif //SHDOCUMENT_SERVER_HPP
