#ifndef BYTEREADER_HPP
#define BYTEREADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "ISocket.hpp"

//std::string getBytesFromLogin(int connection);
//std::vector<char> getBytesFromQuery(int connection);

std::vector<char> getBytesFromLogin(ISocket& socket);
std::vector<char> getBytesFromQuery(ISocket& socket);
void socketForwardBytes(ISocket& from, ISocket& to);

int getQueryLength(unsigned char* buffer);
void forwardBytes(int from, int to);

#endif