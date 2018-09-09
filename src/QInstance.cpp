#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <sys/types.h>

#include <cstring>

#include "QInstance.hpp"

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
  unsigned char pw[9] = { 0x61,0x62,0x63,0x3A,0x61,0x62,0x63,0x03,0x00 };
  ::write(_fd, pw, 9);
  std::cout << "wrote .. " << std::endl;

  char logback[64];
  std::size_t read = 0;

  ssize_t actual = ::read(_fd, logback, 64);
  std::cout << "AA:" << actual << std::endl;
  std::cout << "LOGIN:" << logback[0] << std::endl;
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
