#include <set>

class Connections{
public:
  std::set<int> conns;
  bool isNew(int conn);
  void add(int conn);
};
