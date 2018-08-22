Job* Task::getJob(int fd, std::string bytes) {
  return new Job(fd, bytes);
}
