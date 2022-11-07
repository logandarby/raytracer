#ifndef _DEBUG_H
#define _DEBUG_H

// Debug statements that are turned off by defining the DEBUG flag in compiler using -DDEBUG

#include <string>

void debugPrint(const std::string msg);

void debugAssert(const bool assertion);

#endif