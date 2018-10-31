
#include "QInstance.hpp"
#include "ByteReader.hpp"
#include "ISocket.hpp"

void QInstance::SendLogin() {  
  _socket.Write(std::vector<char>{0x61, 0x62, 0x63, 0x3A, 0x61, 0x62, 0x63, 0x03, 0x00});
  std::cout << "wrote .. " << std::endl;
  auto authByte = _socket.ReadChunk();
  std::cout << "Auth::" << authByte.size() << std::endl;  
}