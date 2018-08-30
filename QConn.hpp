#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class QConn {
private:
  std::string _host;
  bool _ready;
  int _port;
  int _fd;
  std::string _auth;
public:
  QConn(std::string conn);
  QConn();
  std::string getConnString();
  int port() { return _port; };
  std::string host() { return _host; };
};
