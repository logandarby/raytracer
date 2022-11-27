#pragma once

#ifndef _PPM_STREAM_H
#define _PPM_STREAM_H

#include "common/pch.h"

#include "colorStream.h"

// Be sure when using this class to not output anything to std::cout while 

class PPMStream : public ColorStream{
public:
    PPMStream(const int width, const int height, const std::string filename) {
        outfile.open(filename, std::ios::out | std::ios::trunc);
        outfile << "P3\n" << width << ' ' << height << "\n255\n";
    }

    virtual void operator<<(Color rgbPixel) override {
        outfile << rgbPixel.x() << ' '
                << rgbPixel.y() << ' '
                << rgbPixel.z() << std::endl;
    }

    void exportImage() {
        if (outfile.is_open()) {
            outfile.close();
        }
    }

    ~PPMStream() {
        exportImage();
    }
private:
    std::ofstream outfile;
};

#endif