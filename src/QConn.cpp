#include "QConn.hpp"

QConn::QConn(std::string conn) {
  std::stringstream ss(conn);
  std::string part;
  std::vector<std::string> parts{};
  while (std::getline(ss, part, ':')) {
    parts.push_back(part);
  }
  std::cout << "Parts::" << parts.size() << std::endl;
  for (auto &p : parts) {
    std::cout << p << std::endl;
  }

  if (parts.size() == 3) {
    _host = parts[1];
    _port = std::stoi(parts[2]);
    _auth = "";
    _fd = 0;
    _ready = false;
  }

  std::cout << "parsed..." << std::endl;
}

QConn::QConn() {}

std::string QConn::getConnString() {}
