
#include "QInstance.hpp"
#include "ISocket.hpp"

void QInstance::SendLogin() {  
  _socket.Write(std::vector<unsigned char>{0x61, 0x62, 0x63, 0x3A, 0x61, 0x62, 0x63, 0x03, 0x00});
  auto authByte = _socket.ReadChunk();
}