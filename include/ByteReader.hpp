#ifndef BYTEREADER_HPP
#define BYTEREADER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

std::string getBytesFromLogin(int connection);
std::vector<char> getBytesFromQuery(int connection);
#endif