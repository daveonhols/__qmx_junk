#include <string>

class Job {
public:
  Job(int fd, std::string bytes) {
    std::cout << "Job:" << std::endl;
    std::cout <<  fd << std::endl;
    std::cout << bytes << "::" << std::endl;
    _fd = fd;
    _bytes = bytes;
  }
  std::string _bytes;
  int _fd;

};
