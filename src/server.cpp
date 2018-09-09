#include <iostream>
#include <vector>
#include <set>
#include <future>
#include <memory>

#include <netdb.h>
#include <netinet/in.h>

#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <unistd.h>
#include <sys/types.h>

#include "SimpleSocket.hpp"
#include "Job.hpp"
#include "Task.hpp"
#include "QInstance.hpp"
#include "Connections.hpp"
#include "cxxopts.hpp"

void handleJob(std::unique_ptr<Job> job, Connections& conns)
{
  std::cout << "Job::" << std::endl;
  char buffer[1];
  buffer[0] = 3;
  ::write(job->_fd, buffer, 1);
  std::cout << "Job done" << std::endl;  
  while (true)
  {
    auto chars = getBytesFromQuery(job->_fd);

    if (0 == read)
    {
      std::cerr << "going away" << std::endl;
      break;
    }

    //unsigned char one[17] = {0x01,0x02,0x00,0x00,0x11,0x00,0x00,0x00,0xf9,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //::write(job->_fd, one, 17);
    QInstance conn = conns.Take();
    auto response = conn.AcceptBytes(chars);
    conns.Return(std::move(conn));
    ::write(job->_fd, response.data(), response.size());
  }
  std::cerr << "Exiting" << std::endl;
}

int main(int argc, char *argv[])
{

  QConn q1(":localhost:5000");
  QConn q2(":localhost:5001");
  //QInstance qi(q);

  std::deque<QInstance> instances{};
  instances.push_back({q1});
  instances.push_back({q2});

  Connections conns{instances};

  std::vector<std::future<void>> pending;

  cxxopts::Options options("MyProgram", "One line description of MyProgram");
  options.add_options()("s,servers", "servers", cxxopts::value<std::string>())("u,users", "users", cxxopts::value<std::string>());

  auto result = options.parse(argc, argv);

  if (result.count("servers"))
  {
    std::cout << "servers::" << result["servers"].as<std::string>() << std::endl;
  }

  if (result.count("users"))
  {
    std::cout << "users::" << result["users"].as<std::string>() << std::endl;
  }

  std::cout << "hello world2" << std::endl;
  SimpleSocket socket(8844);

  int connection;
  while ((connection = socket.waitForConnection()))
  {
    std::string bytes = getBytesFromLogin(connection);
    std::cout << "bytes:" << bytes << std::endl;
    pending.push_back(std::async(std::launch::async, handleJob, Task::getJob(connection, bytes), std::ref(conns)));
    std::cout << "pushed" << std::endl;
  }
  return 0;
}
