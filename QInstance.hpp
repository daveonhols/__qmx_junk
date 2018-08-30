#include <vector>

class QInstance {
private:
  QConn _conn;
  int _fd;
public:
  QInstance(QConn conn);
  QInstance();
  std::vector<char> AcceptBytes(std::vector<char> bytes);
};

QInstance::QInstance(QConn conn) {
  
  int portno = 0;

  struct sockaddr_in serv_addr;
  struct hostent *server;

  portno = conn.port();
  _fd = ::socket(AF_INET, SOCK_STREAM, 0);

  //std::cout << "QI FD :: " << 
  
  if (_fd < 0)
    std::cout << "ERROR opening socket" << std::endl;

  server = gethostbyname(conn.host().c_str());

  if (server == NULL) {
    std::cout << "ERROR no such host" << std::endl;
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(portno);

  if (connect(_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    std::cout << "ERROR connecting" << std::endl;

  std::cout << "connected ... " << std::endl;
  unsigned char pw[8] = { 0x61,0x62,0x63,0x3A,0x61,0x62,0x63,0x00 };
  ::write(_fd, pw, 8);
  std::cout << "wrote .. " << std::endl;
  
}

std::vector<char> QInstance::AcceptBytes(std::vector<char> bytes) {
  std::cout << "FD::" << _fd << std::endl;
  std::cout << "response going ... " << std::endl;
  ::write(_fd, bytes.data(), bytes.size());
  std::cout << "wrote" << std::endl;
  std::vector<char> rb = getBytesFromQuery(_fd);
  std::cout << "response bytes" << rb.size() << std::endl;
  return rb;
}
