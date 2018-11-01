#include<vector>

#include "Handlers.hpp"
#include "OwnedQInstance.hpp"


void handleJob(ISocket&& userSocket, Connections &conns) {
  std::vector<unsigned char> buffer;
  buffer.push_back(3);
  userSocket.Write(buffer);

  while (true) {
    auto chars = userSocket.ReadChunk();
    OwnedQInstance gateway(conns);
    userSocket.ForwardRemaining(chars, gateway.getSocket());
    gateway.getSocket().ForwardAll(userSocket);
  }
  std::cerr << "Exiting" << std::endl;
}