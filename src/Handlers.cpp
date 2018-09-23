#include "Handlers.hpp"
#include "OwnedQInstance.hpp"

void handleJob(std::unique_ptr<Job> job, Connections &conns) {
  std::cout << "Job::" << std::endl;
  char buffer[1];
  buffer[0] = 3;
  ::write(job->_fd, buffer, 1);
  std::cout << "Job done" << std::endl;

  while (true) {
    auto chars = getBytesFromQuery(job->_fd);

    if (0 == chars.size()) {
      std::cerr << "going away" << std::endl;
      break;
    }

    OwnedQInstance conn(conns);
    conn.getInstance().AcceptBytes(chars);
    forwardBytes(conn.getInstance().fd(), job->_fd);
  }
  std::cerr << "Exiting" << std::endl;
}