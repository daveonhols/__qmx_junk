#ifndef BYTEREADER_HPP
#define BYTEREADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

std::string getBytesFromLogin(int connection);
std::vector<unsigned char> getQueryPreamble(int connection);
long getQueryLength(std::vector<unsigned char>& preamble);
void forwardBytes(int src, int target, std::vector<unsigned char>& preamble,  int length);

#endif