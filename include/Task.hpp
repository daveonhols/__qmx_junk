#include <memory>

class Task {
public:
  static std::unique_ptr<Job> getJob(ISocket& socket, std::vector<char> bytes) { return std::make_unique<Job>(socket, bytes); }
};
