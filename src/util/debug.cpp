#include "debug.h"

#include <string>
#include <iostream>
#include <cassert>

void debugPrint(const std::string msg) {
    #ifdef DEBUG
        std::cerr << msg;
    #else
        (void)msg;
    #endif
}

void debugAssert(const bool assertion) {
    #ifdef DEBUG
        assert(assertion);
    #else
        (void)assertion;
    #endif
}