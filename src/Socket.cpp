#include "Socket.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>

std::vector<char> Socket::ReadChunk() {
  char buffer[1024];
  std::size_t read = 0;
  while (true) {
    ssize_t actual = ::read(this->_fd, buffer + read, 4096 - read);

    if (actual == -1 && (errno == EAGAIN || errno == EINTR)) {
      continue;
    }
    if (actual == -1) {
      std::cerr << "actual -1"
                << "ERR:" << errno << std::endl;
      throw std::runtime_error("Read Error");
    }
    read = actual;
    break;
  }
  auto result = std::vector<char>();
  for (int i = 0; i < read; ++i) {
    result.push_back(buffer[i]);
  }
  return result;
}

std::vector<char> Socket::Read()
{
    std::cout << "READ 11" << std::endl;
    char buffer[1024];
    std::size_t read = 0;
    std::size_t shouldRead = 0;
    while (true) {
      ssize_t actual = ::read(this->_fd, buffer + read, 4096 - read);
      if (actual == 0) {
        break;
      }
      if (actual == -1 && (errno == EAGAIN || errno == EINTR)) {
        continue;
      }
      if (actual == -1) {
        std::cerr << "actual -1"
                  << "ERR:" << errno << std::endl;
        throw std::runtime_error("Read Error");
      }
      read += actual;
      if (read == 4096) {
        break;
      }
      if ((read >= 8) && (0 == shouldRead)) {
        for (int i = 4; i < 8; ++i) {
          shouldRead += buffer[i];
        }
        if (read == shouldRead) {
          break;
        }
        continue;
      }
      if (read == shouldRead) {
        break;
      }
    }
    auto result = std::vector<char>();
    for (int i = 0; i < read; ++i) {
      result.push_back(buffer[i]);
    }

    return result;
  }

  void Socket::Write(std::vector<char> bytes) {
    ::write(_fd, bytes.data(), bytes.size());
  }
