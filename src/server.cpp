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
#include "AsyncLoginHandler.hpp"
#include "QMXListenServer.hpp"

int main(int argc, char *argv[]) {

  QConn q1(":localhost:5000");
  QConn q2(":localhost:5001");

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
  
  AsyncLoginHandler login(cn);
  QMXListenServer qmx(8844, login);
  qmx.Listen();    
}
