#ifndef QINSTANCE_H
#define QINSTANCE_H

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
  int fd() { return _fd; };
  void AcceptBytes(std::vector<char> bytes);
};

#endif