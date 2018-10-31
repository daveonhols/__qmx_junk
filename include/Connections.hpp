#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "QInstance.hpp"

class Connections
{
private:
  std::deque<QInstance> _conns;
  std::mutex _mutex;
  std::condition_variable _available;

public:
  Connections() { _conns = std::deque<QInstance>(); };
  Connections(std::deque<QInstance> conns) : _conns(conns) { };
  QInstance Take();
  void Return(QInstance&& instance);
};

#endif