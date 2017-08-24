#include "Server.hpp"

using namespace nakhoadl;

Server* Server::instance = nullptr;

Server* Server::getInstance() {
    if (Server::instance == nullptr) {
        Server::instance = new Server();
    }

    return Server::instance;
}

Server::Server() {
    createSocket();
    binding();
}

Server::~Server() = default;

Server &Server::createSocket() {
    if ((this->socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw Exception("Can not create socket.");
    }

    std::cout << "Successfully created server." << std::endl;
    return *this;
}

Server &Server::binding() {
    struct sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(this->socketFileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        Exception message("Bind error.");
        throw message;
    }

    std::cout << "Successfully bind and server run at port " << PORT << "." << std::endl;
    return *this;
}

void Server::handl(SocketFileDescriptor &socketFileDescriptor) {
    while (true) {
        char request[100];
        ssize_t bytes = recv(socketFileDescriptor, request, 100, 0);
        if (bytes == 0) {
            ::close(socketFileDescriptor);
            return;
        }
        mutexMain.lock();
        std::cout << "Thread id: " <<  std::this_thread::get_id() << ", Client: "
                  << socketFileDescriptor << ", Bytes = " << bytes
                  << ", Message: " << request << std::endl;
        mutexMain.unlock();
        if (strcmp("end", request) == 0) {
            break;
        }
    }
    ::close(socketFileDescriptor);
}

void Server::start() {
    if (listen(this->socketFileDescriptor, 20) < 0) {
        throw Exception("Listen error");
    }

    std::cout << "Server: waiting for connection." << std::endl;
    SocketFileDescriptor newSocketFileDescriptor;
    struct sockaddr_storage clientAddress;
    socklen_t clientAddressLen = sizeof(clientAddress);
    while (true) {
        if ((newSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress,
                                   (socklen_t*)&clientAddressLen)) < 0) {
            throw Exception("Server can't accept connection.");
        }

        char ipClient[INET_ADDRSTRLEN];
        inet_ntop(clientAddress.ss_family, &((struct sockaddr_in *)&clientAddress)->sin_addr, ipClient,
                  INET_ADDRSTRLEN);
        std::cout << "Server got connection from: " << ipClient << "." << std::endl;
        std::thread newThread(&Server::handl, this,std::ref(newSocketFileDescriptor));
        newThread.detach();
    }
}
