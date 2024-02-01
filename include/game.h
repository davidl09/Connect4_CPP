//
// Created by davidl09 on 12/31/23.
//

#ifndef GAME_H
#define GAME_H

#include <thread>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include "app.h"
#include "bitboard.hpp"
#include "minimaxbit.hpp"

class Game : public App {
public:
    Game(const std::string& name, const ScreenDims size, const std::array<int, 4>& borderWidths = {0}, const int32_t SDLFlags = SDL_INIT_VIDEO, const SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE, const SDL_RendererFlags renderFlags = SDL_RENDERER_ACCELERATED)
        :
    App(name, size, SDLFlags, flags, renderFlags),
    borders(borderWidths), turn_(red),
    rowTokenCount(7), colTokenCount(6),
    columnWidth((size.width - borderWidths[LEFT] - borderWidths[RIGHT]) / rowTokenCount),
    rowHeight((size.height - borderWidths[TOP] - borderWidths[BOTTOM]) / colTokenCount),
    playEnabled(true),
    minimax(9)
    {
        images.insert({"yellowtoken", std::move(loadBMPImageToTexture("images/yellowtoken.bmp"))});
        images.insert({"redtoken", std::move(loadBMPImageToTexture("images/redtoken.bmp"))});
        images.insert({"empty", std::move(loadBMPImageToTexture("images/emptytoken.bmp"))});
        images.insert({"blank", std::move(loadBMPImageToTexture("images/blanktoken.bmp"))});

        for(auto& [name, image] : images) { //adjust image sizes
            image.data.h = image.data.w = std::min(columnWidth, rowHeight);
        }
    }

    void step() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
#ifdef _EMSCRIPTEN_
                emscripten_cancel_main_loop();
#else
                exit(0);
#endif
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x;
                if ((SDL_GetMouseState(&x, nullptr) & SDL_BUTTON(1)) && playEnabled && board.is_legal_move(whichColumn(x))) {
                    handlePlayerTurn(whichColumn(x));
                    playEnabled = false;
                    std::thread{[this]() {
                        handlePlayerTurn(minimax.best_move(this->board));
                        this->playEnabled = true;
                    }}.detach();
                }
            }
        }
        draw();
        showAndClear();
    }

private:
    void drawToken(colour which, int row, int col) {
        const auto colourStr = (which == colour::red ? "redtoken" : (which == colour::yellow ? "yellowtoken" : "empty"));
        pushTexture(images.at(colourStr), {colToScreenX(col), rowToScreenY(row)});
    }

    void blinkWin(unsigned numTimes) {
        playEnabled = false; //disable player input
        auto winArr = this->board.whereWin();
        std::thread([this] {
            for (int i = 0; i < 5; ++i) {
                std::ranges::for_each(this->board.whereWin(), [this](const std::pair<int, int>& p) {
                    this->drawToken(none, p.first, p.second);
                });
                std::this_thread::sleep_for(500ms);
                std::ranges::for_each(this->board.whereWin(), [this](const std::pair<int, int>& p) {
                    this->drawToken(this->board[p.first, p.second], p.first, p.second);
                });
                std::this_thread::sleep_for(500ms);
            }
        }).detach();
    }

    void draw() {
        for (auto square = board.begin(); square < board.end(); ++square) {
            drawToken(*square, square.position().first, square.position().second);
        }
    }

    void undoLast() {
        if (board.removeTopToken(moveSeq.back())) {
            moveSeq.pop_back();
            turn_ = !turn_;
        }

    }

    void handlePlayerTurn(const int columnPlayed) {
        if (board.iswin(red) || board.iswin(yellow)) {
            blinkWin(4);
            board = BitBoard();
            return;
        }
        if (board.place_token(columnPlayed, turn_)) {
            turn_ = !turn_;
            moveSeq.push_back(columnPlayed);
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
    std::atomic<bool> playEnabled;
    std::unordered_map<std::string_view, SDLTextureImg> images;
    std::vector<int> moveSeq;
    MiniMaxBit minimax;
};


#endif //GAME_H
