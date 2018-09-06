#include <string>
#include <iostream>
#include <unistd.h>

std::string getBytesFromLogin(int connection)
{
  char buffer[64];
  for (int i = 0; i < 63; ++i) {
    buffer[i] = 65;
  }
  std::size_t read = 0;
  while(true)
    {
      std::cout << "::" <<  buffer << "::" << std::endl;
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
	  std::cout << "R:" << read << "." << std::endl;
	  std::cout << "X:" << 65 + buffer[read - 2] << "." << std::endl;
	  std::cout << "Read end" << std::endl;
	  break;
	}
    }
  return buffer;
  
}

std::vector<char> getBytesFromQuery(int connection) {  
  char buffer[1024];
  std::size_t read = 0;
  std::size_t shouldRead = 0;
  while(true) {
    ssize_t actual = ::read(connection, buffer + read, 4096 - read);
    std::cout << "AA:" << actual << std::endl;
    std::cout << "!!:" << (short)buffer[0] << ":!!" << std::endl;
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
      std::cerr << "actual -1" << "ERR:" << errno <<std::endl;
      throw std::runtime_error("Read Error");
    }
    read += actual;
    std::cout << "actual" << actual << std::endl;
    if (read == 4096)
    {
      break;
    }
    if ((read >= 8 ) && (0 == shouldRead))
    {
      for (int i = 4; i < 8; ++i) {
        shouldRead += buffer[i];
        std::cout << "Reading" << shouldRead << std::endl;
      }
      std::cout << "Read" << read << std::endl;
      for (size_t j = 0; j < read; ++j)
	      std::cout << (short)buffer[j] << "." << std::endl;
      if (read == shouldRead) {
	      break;
      }
      continue;
    }
    if (read == shouldRead) {
      break;
    }      
  }
  std::cout << "read::" << read << std::endl;

  auto result = std::vector<char>();
  for (int i =0 ; i < read; ++i) {
    result.push_back(buffer[i]);
  }
  
  return result;
}
