#include <iostream>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include <sys/types.h>
#include <cstring>


#include "ISocket.hpp"

ISocket::ISocket(std::string host, int port) {
    std::cout << "connecting back end" << std::endl;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    _fd = ::socket(AF_INET, SOCK_STREAM, 0);

    if (_fd < 0)
        std::cout << "ERROR opening socket" << std::endl;

    server = gethostbyname(host.c_str());

    if (server == NULL) {
        std::cout << "ERROR no such host" << std::endl;
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "ERROR connecting" << std::endl;
    }
    std::cout << "connected" << std::endl;
}

ISocket::~ISocket() {
    if (_fd > 0) {
        std::cout << "closing::" << _fd << std::endl;
        ::close(_fd);
    }
}