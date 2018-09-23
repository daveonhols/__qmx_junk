#include "AsyncLoginHandler.hpp"
#include "ByteReader.hpp"
#include "Handlers.hpp"
#include "Task.hpp"

#include <string>
#include <future>
#include <iostream>
#include <memory>
#include <set>
#include <vector>


void AsyncLoginHandler::onLogin(int fd) {
    std::string bytes = getBytesFromLogin(fd);
    _pending.push_back(
        std::async(
            std::launch::async, 
            handleJob,                                 
            Task::getJob(fd, bytes),
            std::ref(_conns))
    );
}