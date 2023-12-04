
#include "bitboard.hpp"
#include "minimaxbit.hpp"

#include "SDL.h"

class GameBoard {
public:
private:

};

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b) {
    // Draw the circle using the midpoint circle algorithm
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

        // Octant 1
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        // Octant 2
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        // Octant 3
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        // Octant 4
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        // Octant 5
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        // Octant 6
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        // Octant 7
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        // Octant 8
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Uint8 r, Uint8 g, Uint8 b) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(int argc, char* argv[]){

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "Could not initialize SDL";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Connect4!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Draw a circle with radius 50, RGB color (255, 0, 0), and center at (400, 300)
    drawFilledCircle(renderer, 400, 300, 50, 255, 0, 0);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for the user to close the window
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

    BitBoard b;
    /*
    int minimaxdepth;
    try{
        minimaxdepth = (argc > 1 ? std::stoi(argv[1]) : 11);
    }catch(...){std::cout << ("Invalid depth option, using default=11\n");}

    auto algo = MiniMaxBit(minimaxdepth);

    b.print_board();

    int move;
    while(true){

        std::cout << "Enter your move\n";
        std::cin >> move;
        --move;

        if(!b.is_legal_move(move)){
            std::cout << "That was an invalid move, try again\n";
            continue;
        }

        b.place_token(move, red);
        b.print_board();

        std::cout << "AI plays...\n";
        move = algo.best_move(b);
        std::cout << "AI played in column: " << move << "\n";

        b.place_token(move, ai);
        b.print_board();

        if(b.iswin(ai)){
            std::cout << "AI wins!\n";
            exit(0);
        }
        if(b.iswin(human)){
            std::cout << "You win!\n";
            exit(0);
        }
        if(b.isdraw()){
            std::cout << "Draw...\n";
            exit(0);
        }
    }
*/
}
