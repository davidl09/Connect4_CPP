//
// Created by davidl09 on 12/31/23.
//

#ifndef GAME_H
#define GAME_H

#include <complex>
#include <map>
#include "app.h"
#include "bitboard.hpp"

class Game : public App {
public:
    Game(const std::string& name, const ScreenDims size, const std::array<int, 4>& borderWidths = {0}, const int32_t SDLFlags = SDL_INIT_VIDEO, const SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE, const SDL_RendererFlags renderFlags = SDL_RENDERER_ACCELERATED)
        :
    App(name, size, SDLFlags, flags, renderFlags),
    borders(borderWidths), turn_(red),
    rowTokenCount(7), colTokenCount(6),
    columnWidth((size.width - borderWidths[LEFT] - borderWidths[RIGHT]) / rowTokenCount),
    rowHeight((size.height - borderWidths[TOP] - borderWidths[BOTTOM]) / colTokenCount)
    {
        images.insert({"yellowtoken", std::move(loadBMPImageToTexture("images/yellowtoken.bmp"))});
        images.insert({"redtoken", std::move(loadBMPImageToTexture("images/redtoken.bmp"))});
    }

    void step() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                emscripten_cancel_main_loop();
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x;
                if (SDL_GetMouseState(&x, nullptr) == SDL_BUTTON(1)) {
                    handlePlayerTurn(whichColumn(x));
                }
            }
        }
        draw();
        showAndClear();

    }

private:
    void drawToken(colour which, int row, int col) {
        const auto colourStr = (which == colour::red ? "redtoken" : (which == colour::yellow ? "yellowtoken" : "empty"));
        pushTexture(images.at(colourStr), SDL_Rect(colToScreenX(col), rowToScreenY(row), columnWidth, rowHeight));
    }

    void draw() {

    }

    void handlePlayerTurn(int columnPlayed) {
        if (board.place_token(columnPlayed, turn_)) {
            turn_ = !turn_;
        }
    }

    enum BORDERS {
        LEFT, RIGHT, TOP, BOTTOM,
    };

    [[nodiscard]]
    constexpr int whichColumn(const int mouseX) const {
        const auto pos = rowTokenCount * mouseX / (size.width - borders[LEFT]);
        if (not inRange(0, rowTokenCount, pos)) return -1;
        return pos;
    }

    [[nodiscard]]
    constexpr int whichRow(const int mouseY) const {
        const auto row = colTokenCount - 1 - colTokenCount * mouseY / (size.height - borders[TOP]);
        if (not inRange(0, colTokenCount, row)) return -1;
        return row;
    }

    [[nodiscard]]
    constexpr int colToScreenX(const int column) const {
        return column * columnWidth + borders[LEFT];
    }

    [[nodiscard]]
    constexpr int rowToScreenY(const int row) const {
        return (colTokenCount - row - 1) * rowHeight + borders[TOP];
    }

    std::array<int, 4> borders; //left, right, top, bottom;
    const int rowTokenCount, colTokenCount;
    int columnWidth, rowHeight;
    BitBoard board;
    SDL_Event event;
    colour turn_;
    std::unordered_map<std::string_view, SDLTextureImg> images;
};


#endif //GAME_H
