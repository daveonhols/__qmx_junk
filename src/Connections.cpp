#include "Connections.hpp"

bool Connections::isNew(int conn) {
  return 1 == conns.count(conn);
}

void Connections::add(int conn) {
  conns.insert(conn);
}
