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

#include <chrono>

#include "SimpleSocket.hpp"
#include "Job.hpp"
#include "Task.hpp"
#include "QInstance.hpp"
#include "Connections.hpp"
#include "cxxopts.hpp"

void handleJob(std::unique_ptr<Job> job, Connections& conns)
{
  char buffer[1];
  buffer[0] = 3;
  ssize_t wrote = ::write(job->_fd, buffer, 1);
  if (wrote < 1) return;
  while (true)
  {
    auto query = getQueryPreamble(job->_fd);
    auto s = std::chrono::steady_clock::now();
    int length = getQueryLength(query);
    std::cout << "T1:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    // std::cout << "Query Length:" << length << std::endl;
    QInstance conn = conns.Take();
    std::cout << "T2:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    // send query from user to Kdb
    forwardBytes(job->_fd, conn.fd(), query, length - 8); // - 8 because we have read pre-amble
    std::cout << "T3:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    auto response = getQueryPreamble(conn.fd());
    std::cout << "T4:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    auto responseLength = getQueryLength(response);
    std::cout << "T5:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    //std::cout << "Response Length:" << responseLength << std::endl;
    forwardBytes(conn.fd(), job->_fd, response, responseLength - 8); // - 8 because we have read pre-amble
    std::cout << "T6:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    conns.Return(std::move(conn));
    std::cout << "T7:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    //::write(job->_fd, response.data(), response.size());
  }
  std::cerr << "Exiting" << std::endl;
}

int main(int argc, char *argv[])
{
  
  unsigned int bb[8] = {0x0, 0x0, 0x0, 0x0, 0xc6, 0x34, 0x0c, 0x00};
  std::vector<unsigned char> buff{bb, std::end(bb)};
  std::cout << "size::" << getQueryLength(buff) << std::endl;
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
