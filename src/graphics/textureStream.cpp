#include "textureStream.h"

#include "common/pch.h"
#include "util/debug.h"
#include <SDL.h>
#include <SDL_image.h>

void TextureStream::Create(SDL_Renderer *renderer, const int width, const int height) {
    debugAssert(renderer != nullptr);
    debugAssert(width > 0);
    debugAssert (height > 0);

    m_renderer = renderer;
    m_height = height;
    m_width = width;
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        width, height);
    if (!m_texture) {
        SDL_Log("Could not create blank texture!");
        SDL_LogError(0, SDL_GetError());
    }
    debugAssert(m_texture != nullptr);
}

TextureStream::~TextureStream() {
    SDL_DestroyTexture(m_texture);
}

bool TextureStream::addPixel(const Color rgbPixel, const int x, const int y) {
    debugAssert(x < m_width);
    debugAssert(y < m_height);
    int category = SDL_SetRenderTarget(m_renderer, m_texture);
    if (category < 0) {
        SDL_LogError(category, SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(m_renderer,
        rgbPixel.x(), rgbPixel.y(), rgbPixel.z(), SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(m_renderer, x, y);
    SDL_SetRenderTarget(m_renderer, NULL);
    return true;
}

bool TextureStream::resize(const int width, const int height) {
    m_width = width;
    m_height = height;
    resetPixelIndex();
    SDL_DestroyTexture(m_texture);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        width, height);
    if (!m_texture) {
        SDL_Log("Could not resize texture!");
        SDL_LogError(0, SDL_GetError());
        return false;
    }
    return true;
}

TextureStream& TextureStream::operator<<(const Color rgbPixel) {
    if (m_pixelIndex >= m_width * m_height) {
        return *this;
    }
    const int x = m_pixelIndex % m_width;
    const int y = m_pixelIndex / m_width;
    addPixel(rgbPixel, x, y);
    m_pixelIndex ++;
    return *this;
}

void TextureStream::resetPixelIndex() {
    m_pixelIndex = 0;
}

SDL_Texture *TextureStream::getSDLTexture() {
    return m_texture;
}

void TextureStream::saveTexture(const char* file_name, ImageFormat iformat) {
    SDL_Texture* target = SDL_GetRenderTarget(m_renderer);
    SDL_SetRenderTarget(m_renderer, m_texture);
    int width, height;
    SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(m_renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    if (iformat == IMAGEFORMAT_PNG)
        IMG_SavePNG(surface, file_name);
    else if (iformat == IMAGEFORMAT_JPG)
        IMG_SaveJPG(surface, file_name, 60);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(m_renderer, target);
}



void TextureStream::drawDebugRect() {
    int category = SDL_SetRenderTarget(m_renderer, m_texture);
    if (category < 0) {
        SDL_LogError(category, SDL_GetError());
    }

    SDL_Rect rect{0, 0, m_width / 2, m_height / 2};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &rect);

    SDL_SetRenderTarget(m_renderer, NULL);

}

