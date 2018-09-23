#include <deque>
#include <future>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

#include <netdb.h>
#include <netinet/in.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/types.h>
#include <unistd.h>

#include <chrono>

//#include "Connections.hpp"
#include "Job.hpp"
#include "SimpleSocket.hpp"
#include "Task.hpp"
#include "cxxopts.hpp"
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

int main(int argc, char *argv[]) {

  QConn q1(":localhost:5000");
  QConn q2(":localhost:5001");
  // QInstance qi(q);

  std::vector<std::future<void>> pending{};

  std::deque<QInstance> instances{};
  instances.push_back({q1});
  instances.push_back({q2});

  std::deque<QInstance> c{};
  c.push_back(q1);
  c.push_back(q2);
  Connections cn{c};

  cxxopts::Options options("MyProgram", "One line description of MyProgram");
  options.add_options()("s,servers", "servers", cxxopts::value<std::string>())(
      "u,users", "users", cxxopts::value<std::string>());

  auto result = options.parse(argc, argv);

  if (result.count("servers")) {
    std::cout << "servers::" << result["servers"].as<std::string>()
              << std::endl;
  }

  if (result.count("users")) {
    std::cout << "users::" << result["users"].as<std::string>() << std::endl;
  }

  std::cout << "hello world2" << std::endl;
  SimpleSocket socket(8844);

  int connection;
  while ((connection = socket.waitForConnection())) {
    std::string bytes = getBytesFromLogin(connection);
    std::cout << "bytes:" << bytes << std::endl;
    pending.push_back(std::async(std::launch::async, handleJob,
                                 Task::getJob(connection, bytes),
                                 std::ref(cn)));
    std::cout << "pushed" << std::endl;
  }
  return 0;
}
