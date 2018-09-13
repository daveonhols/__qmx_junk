#include <chrono>
#include <iostream>
#include "ByteReader.hpp"

std::string getBytesFromLogin(int connection)
{
  char buffer[64];
  for (int i = 0; i < 63; ++i)
  {
    buffer[i] = 65;
  }
  std::size_t read = 0;
  while (true)
  {
    ssize_t actual = ::read(connection, buffer + read, 4096 - read);
    if (actual == 0)
    {
      break;
    }
    if (actual == -1 && (errno == EAGAIN || errno == EINTR))
    {
      continue;
    }
    if (actual == -1)
    {
      throw std::runtime_error("Read Error");
    }
    read += actual;
    if (read == 4096)
    {
      break;
    }
    if ((read > 0) && buffer[read - 1] == '\0')
    {
      break;
    }
  }
  return buffer;
}

std::vector<unsigned char> getQueryPreamble(int connection) {
  auto s = std::chrono::steady_clock::now();
  std::cout << "T1:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
  const size_t psize = 8;

  char buffer[psize] = {0};
  std::cout << "T2:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;

  std::size_t read = 0;

  while (true)
  {
    std::cout << "T3:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    auto bb =  buffer+read;
    std::cout << "T3a:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    size_t pr = psize - read;
    std::cout << "T3b:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    ssize_t actual = ::read(connection, bb, pr);
    std::cout << "T4:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    //std::cout << "AA:" << std::endl;
    if (actual == 0)
    {
      break;
    }
    std::cout << "T5:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    if (actual == -1 && (errno == EAGAIN || errno == EINTR))
    {
      continue;
    }
    std::cout << "T6:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    if (actual == -1)
    {
      throw std::runtime_error("Read Error");
    }
    std::cout << "T7:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    read += actual;
    std::cout << "T8:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
    if (read == psize) {
      std::cout << "T9:" <<  std::chrono::duration_cast<std::chrono::milliseconds>  (std::chrono::steady_clock::now() - s).count() << std::endl;
      return std::vector<unsigned char>{buffer, std::end(buffer)};
    }
  }
}

long getQueryLength(std::vector<unsigned char>& preamble) {
  long len = 0;
  len += preamble[4];
  len += preamble[5] << 8;
  len += preamble[6] << 16;
  len += preamble[7] << 24;
  return len;
}

void forwardBytes(int srcFd, int target, std::vector<unsigned char>& preamble, int len) {
  
  ::write(target, preamble.data(), preamble.size());

  std::size_t totalRead = 0;
  
  while (totalRead < len) {
    std::size_t loopRead = 0;
    const int bsize = 1024;
    char buffer[bsize];
    while (true) {
      ssize_t actual = ::read(srcFd, buffer + loopRead, bsize - loopRead);
      if (actual == 0)
      {
        std::cout << "ACTUAL ZERO" << std::endl;
        break;
      }
      if (actual == -1 && (errno == EAGAIN || errno == EINTR))
      {
        continue;
      }
      if (actual == -1)
      {
        throw std::runtime_error("Read Error");
      }

      loopRead += actual;
      totalRead += actual;
      if (loopRead == bsize || totalRead == len)
      {
        break;
      }
    }
    ::write(target, buffer, loopRead);
  }
}

