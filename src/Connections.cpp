#include "Connections.hpp"
#include "QInstance.hpp"

QInstance Connections::Take() {

  std::unique_lock<std::mutex> guard(_mutex);
  while (_conns.size() == 0) {
    _available.wait(guard);
  }
  QInstance next = std::move(_conns.front());
  _conns.pop_front();
  return next;

}

void Connections::Return(QInstance &&instance) {

  std::unique_lock<std::mutex> guard(_mutex);
  _conns.push_back(std::move(instance));
  _available.notify_one();
  
}
