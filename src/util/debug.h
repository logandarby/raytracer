#ifndef _DEBUG_H
#define _DEBUG_H

#include <string>
#include <iostream>
#include <assert.h>

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

#endif