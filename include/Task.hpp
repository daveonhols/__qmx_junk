//#include "Job.hpp"
#include <memory>

class Task {
public:
  static std::unique_ptr<Job> getJob(int fd, std::string bytes) { return std::make_unique<Job>(fd, bytes); }
};
