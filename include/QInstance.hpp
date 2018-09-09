#ifndef QINSTANCE_HPP
#define QINSTANCE_HPP

#include <vector>
#include "ByteReader.hpp"
#include "QConn.hpp"

class QInstance {
private:
  QConn _conn;
  int _fd;
public:
  QInstance(QConn conn);
  QInstance();
  std::vector<char> AcceptBytes(std::vector<char> bytes);
};

#endif