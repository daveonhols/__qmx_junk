#include <memory>

#include "Job.hpp"
#include "Connections.hpp"

void handleJob(std::unique_ptr<Job> job, Connections &conns);
