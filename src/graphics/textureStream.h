#ifndef _TEXTURESTREAM_H
#define _TEXTURESTREAM_H

// Implement a way of storing pixel data to be rendered to the view.

#include "common/color.h"

class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;

enum ImageFormat {
    IMAGEFORMAT_PNG,
    IMAGEFORMAT_JPG
};

class TextureStream {
public:
    TextureStream() = default;
    ~TextureStream();
    void Create(SDL_Renderer *renderer, const int width = 300, const int height = 200);
    bool addPixel(const Color rgbPixel, const int x, const int y);
    bool resize(const int width, const int height);
    void drawDebugRect();
    SDL_Texture *readSDLTexture();
    void saveTexture(const char* file_name, ImageFormat iformat = IMAGEFORMAT_PNG);

    // Add next RGB pixel
    TextureStream& operator<<(const Color rgbPixel);
private:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture = nullptr;
    int m_width;
    int m_height;
    int m_pixelIndex = 0;
private:
    void resetPixelIndex();
};

#endif