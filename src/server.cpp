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
#include "Socket.hpp"
#include "Task.hpp"
#include "cxxopts.hpp"
#include "OwnedQInstance.hpp"
#include "AsyncLoginHandler.hpp"
#include "QMXListenServer.hpp"

int main(int argc, char *argv[]) {

  QConn q1(":localhost:5000");
  QConn q2(":localhost:5001");

  std::deque<QInstance> c{};
  Socket s1 (q1.host(), q1.port());
  Socket s2 (q2.host(), q2.port());
  c.push_back(QInstance(q1, s1));
  c.push_back(QInstance(q2, s2));
  
  std::cout << "HAS::" << c.size() << std::endl;

  std::for_each(c.begin(), c.end(), [](auto& conn){ std::cout << "XXX" << std::endl; conn.SendLogin(); });

  Connections cn{std::move(c)};

  std::cout << "starting listen <<" << std::endl;

  AsyncLoginHandler login(cn);
  QMXListenServer qmx(8844, login);
  qmx.Listen();    
}
