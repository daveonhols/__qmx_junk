#include <string>

class Job {
public:
  Job(int fd, std::string bytes) {
    _fd = fd;
    _bytes = bytes;
  }
  std::string _bytes;
  int _fd;

};
