#include "jpgStream.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

JPGStream::JPGStream(const int width, const int height, const std::string filename, const int quality) :
    m_filename{filename}, m_width{width}, m_height{height}, m_quality{quality}
{
    m_data.reserve(width * height * s_NO_OF_CHANNELS);
}

void JPGStream::exportImage() {
    if (!m_isExported) {
        m_data.resize(m_width * m_height * s_NO_OF_CHANNELS, 0);
        stbi_write_jpg(m_filename.c_str(), m_width, m_height, s_NO_OF_CHANNELS, m_data.data(), m_quality);
        m_isExported = true;
    }
}

void JPGStream::operator<<(Color rgbPixel) {
    m_data.emplace_back(rgbPixel.x());
    m_data.emplace_back(rgbPixel.y());
    m_data.emplace_back(rgbPixel.z());
}
