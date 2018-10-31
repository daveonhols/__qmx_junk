#ifndef QINSTANCE_H
#define QINSTANCE_H

#include <vector>
#include "ByteReader.hpp"
#include "QConn.hpp"
#include "ISocket.hpp"

class QInstance {
private:
  QConn _conn;
  ISocket& _socket;
public:
  void SendLogin();
  QInstance(QConn conn, ISocket& socket) : _conn(conn), _socket(socket) {};  
  QInstance();
  ISocket& getSocket() { return _socket;}
};

#endif