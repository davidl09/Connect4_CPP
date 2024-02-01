#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <SDL2/SDL.h>
#include "game.h"


void run(void *args) {
    static Game game{"Test", {800, 600}};
    game.step();
}

int main(int, char *[]) {

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(run, nullptr, 0, -1);
#else
    while (true) {
        run(nullptr);
    }
#endif
}
