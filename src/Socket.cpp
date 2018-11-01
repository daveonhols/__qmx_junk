#include "Socket.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <cstring>


Socket::Socket(std::string host, int port) {
    struct sockaddr_in serv_addr;
    struct hostent *server;

    _fd = ::socket(AF_INET, SOCK_STREAM, 0);

    if (_fd < 0) {
        std::cerr << "ERROR opening socket" << std::endl;
    }
    server = gethostbyname(host.c_str());

    if (server == NULL) {
        std::cerr << "ERROR no such host" << std::endl;
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR connecting" << std::endl;
    }
}

Socket::~Socket() {
    if (_fd > 0) {
        ::close(_fd);
    }
}

std::vector<unsigned char> Socket::ReadChunk() {
  unsigned char buffer[CHUNK_SIZE];
  std::size_t read = 0;
  while (true) {
    ssize_t actual = ::read(this->_fd, buffer + read, CHUNK_SIZE - read);

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
  if (0 == read)  {
    std::runtime_error("Zero read - client went away");
  }
  auto result = std::vector<unsigned char>();
  for (int i = 0; i < read; ++i) {
    result.push_back(buffer[i]);
  }
  return result;
}

std::vector<unsigned char> Socket::ReadFully() {
    unsigned char buffer[CHUNK_SIZE];
    std::size_t read = 0;
    std::size_t shouldRead = 0;
    while (true) {
      ssize_t actual = ::read(this->_fd, buffer + read, CHUNK_SIZE - read);
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
      if (read == CHUNK_SIZE) {
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
    auto result = std::vector<unsigned char>();
    for (int i = 0; i < read; ++i) {
      result.push_back(buffer[i]);
    }

    return result;
  }

void Socket::Write(std::vector<unsigned char> bytes) {
    ::write(_fd, bytes.data(), bytes.size());
  }

void Socket::ForwardAll(ISocket& to) {
  ForwardRemaining(ReadChunk(), to);
}

void Socket::ForwardRemaining(std::vector<unsigned char> initial, ISocket& to) {
  long length = getQueryLength(initial);
  long done = initial.size();
  to.Write(initial);
  while (done < length) {
    auto chunk = ReadChunk();
    to.Write(chunk);
    done += chunk.size();
  }
}

long Socket::getQueryLength(std::vector<unsigned char> header) {
  long len = 0;
  len += header[4];
  len += header[5] << 8;
  len += header[6] << 16;
  len += header[7] << 24;
  return len;
}

