#ifndef ISOCKET_H
#define ISOCKET_H

#include <string>   
#include <vector>
#include <iostream>

class ISocket {
    public:
        virtual ~ISocket() {};
        virtual std::vector<unsigned char> ReadFully() = 0;
        virtual std::vector<unsigned char> ReadChunk() = 0;
        virtual void ForwardRemaining(std::vector<unsigned char> initial, ISocket& to) = 0;
        virtual void ForwardAll(ISocket& to) = 0;
        virtual void Write(std::vector<unsigned char>) = 0;
};

#endif