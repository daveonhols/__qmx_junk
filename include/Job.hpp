#include <string>
#include "ISocket.hpp"

class Job {
public:
  Job(ISocket& socket, std::vector<char> bytes) : _socket(socket) {
    _bytes = bytes;
    socket.Show();
    _socket.Show();
  }
  std::vector<char> _bytes;
  ISocket& _socket;
};
