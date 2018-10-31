#ifndef ISOCKET_H
#define ISOCKET_H

#include <string>   
#include <vector>
#include <iostream>

class ISocket {

    public:
        ISocket(int fd) : _fd(fd) {};
        ISocket(std::string, int port);
        virtual ~ISocket();
        virtual std::vector<char> Read() = 0;
        virtual std::vector<char> ReadChunk() = 0;
        virtual void Write(std::vector<char>) = 0;
        virtual void Show() {std::cout << "Base" << std::endl;}
    protected:
        int _fd;

};

#endif