//
// Created by davidl09 on 12/31/23.
//

#ifndef APP_H
#define APP_H

#include <emscripten.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <unordered_map>

template<class SDL_Type>
using sdl_ptr = std::unique_ptr<SDL_Type, void (*)(SDL_Type *)>;

struct ScreenDims {
    ScreenDims(const int x, const int y)
        : width(x), height(y) {}

    int width, height;
};

struct RGB {
    union {
        struct {
            uint8_t red, green, blue;
        };
        uint8_t data[3];
    };

    uint8_t& operator[](const uint8_t index) {
        return data[index];
    }
};

struct RGBA {
    union {
        struct {
            uint8_t red, green, blue, alpha;
        };
        uint8_t data[4];
    };

    uint8_t& operator[](const uint8_t index) {
        return data[index];
    }
};



class App {
protected:
    struct SDLTextureImg;
public:
    App(const std::string& name, const ScreenDims size, const int32_t init_flags = SDL_INIT_VIDEO, const SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE, const SDL_RendererFlags renderFlags = SDL_RENDERER_ACCELERATED)
        :
    initStatus(SDL_Init(init_flags)), //must be initialized first to allow calling SDL_Init before SDL_CreateWindow
    window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.width, size.height, flags), SDL_DestroyWindow),
    renderer(SDL_CreateRenderer(window.get(), -1, renderFlags), SDL_DestroyRenderer),
    size(size)
    {
        if (initStatus) {
            std::cerr << "Could not init SDL\n";
            exit(1);
        }
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
        showAndClear();
    }

    ~App() {
        SDL_Quit();
    }

    [[nodiscard]]
    auto loadBMPImageToTexture(const std::string& pathname) const {
        sdl_ptr<SDL_Surface> image{SDL_LoadBMP(pathname.c_str()), SDL_FreeSurface};
        if (!image) {
            throw std::invalid_argument("Could not locate BMP file!");
        }
        return SDLTextureImg(*this, std::move(image));
    }

    void pushTexture(const SDLTextureImg& texture, const SDL_Rect where) const {
        SDL_RenderCopy(renderer.get(), texture.texture.get(), &where, &texture.data);
    }

    void showAndClear() {
        SDL_RenderPresent(renderer.get());
        clear();
    }

    void clear() const {
        SDL_RenderClear(renderer.get());
    }

protected:
    const size_t initStatus;
    sdl_ptr<SDL_Window> window;
    sdl_ptr<SDL_Renderer> renderer;
    ScreenDims size;
    std::unordered_map<std::string_view, sdl_ptr<SDL_Texture>> images;

    void resize() { //updates size data
        SDL_GetWindowSize(window.get(), &size.width, &size.height);
    }

    struct SDLTextureImg {
        SDLTextureImg(const App& app, const sdl_ptr<SDL_Surface>& surface)
            : texture(SDL_CreateTextureFromSurface(app.renderer.get(), surface.get()), SDL_DestroyTexture), data{0, 0, surface->w, surface->h}
        {}

        SDLTextureImg(SDLTextureImg &&old) noexcept
            : texture(std::move(old.texture)), data(old.data)
        {}

        SDLTextureImg(SDLTextureImg &old) = delete;

        SDLTextureImg& operator=(SDLTextureImg &&old) noexcept {
            texture = std::move(old.texture);
            data = old.data;
            return *this;
        }

        SDLTextureImg& operator=(SDLTextureImg&) = delete;

        sdl_ptr<SDL_Texture> texture;
        SDL_Rect data;
    };
};


#endif //APP_H
