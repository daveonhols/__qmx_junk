
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "QConn.hpp"

QConn::QConn(std::string conn) {
  std::stringstream ss(conn);
  std::string part;
  std::vector<std::string> parts{};
  while (std::getline(ss, part, ':')) {
    parts.push_back(part);
  }
  for (auto &p : parts) {
    std::cout << p << std::endl;
  }

  if(parts.size() < 3) {
    throw new std::runtime_error("Badly configured QConn");
  }

  _host = 0 == parts[1].length() ? "localhost" : parts[1];
  _port = std::stoi(parts[2]);

  if (parts.size() == 5) {
    _auth = parts[3] + ":" + parts[4];
  }
}