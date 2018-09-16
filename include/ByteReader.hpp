#ifndef BYTEREADER_HPP
#define BYTEREADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <vector>

std::string getBytesFromLogin(int connection);
std::vector<char> getBytesFromQuery(int connection);
int getQueryLength(unsigned char* buffer);
void forwardBytes(int from, int to);

#endif