#include "AsyncLoginHandler.hpp"
#include "Handlers.hpp"
#include "Task.hpp"
#include "Socket.hpp"

#include <string>
#include <future>
#include <iostream>
#include <memory>
#include <set>
#include <vector>


void AsyncLoginHandler::onLogin(int fd) {
    
    Socket sock(fd);
    std::vector<unsigned char> bytes = sock.ReadChunk();

    _pending.push_back(
        std::async(
            std::launch::async, 
            handleJob,                                 
            std::move(sock),
            std::ref(_conns))
    );
}