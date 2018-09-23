#include "SimpleSocket.hpp"

#include <cstring> // strerror
#include <memory>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <strings.h>

#include <unistd.h> // ::close

using namespace std::literals;

SimpleSocket::SimpleSocket(int port) {
  sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    throw std::runtime_error("Failed to create socket");
  }

  struct sockaddr_in serv_addr;
  ::bzero((char *)&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  if (::bind(sockfd, reinterpret_cast<sockaddr *>(&serv_addr),
             sizeof(serv_addr)) < 0) {
    throw std::runtime_error("Failed to bind to port: "s +
                             std::strerror(errno));
  }
}

SimpleSocket::~SimpleSocket() { ::close(sockfd); }

int SimpleSocket::waitForConnection() {
  int result = ::listen(sockfd, 5);
  if (result < 0) {
    throw std::runtime_error("Listen failed");
  }
  sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);
  int newsockfd =
      ::accept(sockfd, reinterpret_cast<sockaddr *>(&cli_addr), &clilen);
  if (newsockfd < 0) {
    throw std::runtime_error("accept failed");
  }
  return newsockfd;
}
