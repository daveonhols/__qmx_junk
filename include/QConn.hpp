#ifndef QCONN_H
#define QCONN_H

#include <string>

class QConn {
private:
  std::string _host;
  bool _ready;
  int _port;
  std::string _auth;
public:
  QConn(std::string conn);
  std::string auth() {return _auth; };
  int port() { return _port; };
  std::string host() { return _host; };
};

#endif