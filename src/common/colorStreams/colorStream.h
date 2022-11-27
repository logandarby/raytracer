#pragma once

#ifndef _COLOR_STREAM_H
#define _COLOR_STREAM_H

#include "../color.h"

// Wrapper class used to stream RGB colors to some output

class ColorStream {
public:
    virtual ~ColorStream() = default;
    virtual void operator<<(Color rgbPixel) = 0;
};

#endif