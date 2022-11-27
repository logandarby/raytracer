#pragma once

#ifndef _JPG_STREAM_H
#define _JPG_STREAM_H

#include "common/pch.h"

#include "colorStream.h"

class JPGStream : public ColorStream {
public:
    JPGStream(const int width, const int height, const std::string filename, const int quality = 100);
    ~JPGStream() = default;
    virtual void exportImage() override;
    virtual void operator<<(Color rgbPixel) override;
private:
    std::vector<unsigned char> m_data;
    const std::string m_filename;
    const int m_width;
    const int m_height;
    const int m_quality;

    bool m_isExported = false;

    static const unsigned int s_NO_OF_CHANNELS = 3;
};

#endif