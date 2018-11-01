#include "ISocket.hpp"
#include <string>

class Job {
  public:
    Job(ISocket &socket, std::vector<char> bytes) : _socket(socket) {
      _bytes = bytes;
    }

  private:
    std::vector<char> _bytes;
    ISocket &_socket;
};
