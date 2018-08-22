#include <iostream>
#include <vector>
#include <set>
#include <future>
#include <memory>

#include <netdb.h>
#include <netinet/in.h>


#include <cstring> // strerror
#include <cstdio>
#include <cstdlib>
#include <cerrno>

#include <unistd.h>
#include <sys/types.h>

#include "ByteReader.hpp"
#include "SimpleSocket.hpp"
#include "Job.hpp"
#include "Task.hpp"

#include "Connections.hpp"


void handleJob(std::unique_ptr<Job> job){
  std::cout << "Job::" << std::endl;
  char buffer[1];
  buffer[0] = 3;
  ::write(job->_fd, buffer, 1);
  std::cout << "Job done" << std::endl;
  while(true) {
    int read = getBytesFromQuery(job->_fd);
    if (0 == read) {
      std::cerr << "going away" << std::endl;
      break;
    }
     
    unsigned char one[17] = {0x01,0x02,0x00,0x00,0x11,0x00,0x00,0x00,0xf9,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    ::write(job->_fd, one, 17);
  }
  std::cerr << "Exiting" << std::endl;

  //::close(job->_fd);
}

int main() {
  std::vector<std::future<void>> pending;

  auto connections = Connections();
  
  std::cout << "hello world2" << std::endl;
  SimpleSocket socket(8101);


  int connection;
  while ((connection = socket.waitForConnection())) {
    bool newUser = connections.isNew(connection);
    std::cout << "New ?? " << (newUser ? "Yes" : "No") << std::endl;
    std::string bytes = getBytesFromLogin(connection);
    
    std::cout <<"bytes:" << bytes << std::endl;
    pending.push_back(std::async(std::launch::async, handleJob, Task::getJob(connection, bytes)));
    std::cout << "pushed" << std::endl;
  }
  return 0;
}
