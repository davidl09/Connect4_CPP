#include <emscripten/emscripten.h>
#include <SDL2/SDL.h>
#include "game.h"


void run(void *args) {
    static Game game{"Test", {800, 600}};
    game.step();
}

int main(int, char *[]) {
    emscripten_set_main_loop_arg(run, nullptr, 0, true);
}