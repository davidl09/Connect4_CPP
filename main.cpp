
#include "bitboard.hpp"
#include "minimaxbit.hpp"

MiniMaxBit algo;
BitBoard board;

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

void play() {
    int move;
    std::cout << "Enter your move\n";
    std::cin >> move;
    --move;

    if(!board.is_legal_move(move)){
        std::cout << "That was an invalid move, try again\n";
        return;
    }

    board.place_token(move, red);
    board.print_board();

    std::cout << "AI plays...\n";
    move = algo.best_move(board);
    std::cout << "AI played in column: " << move << "\n";

    board.place_token(move, ai);
    board.print_board();

    if(board.iswin(ai)){
        std::cout << "AI wins!\n";
        exit(0);
    }
    if(board.iswin(human)){
        std::cout << "You win!\n";
        exit(0);
    }
    if(board.isdraw()){
        std::cout << "Draw...\n";
        exit(0);
    }
}

int main(int argc, char* argv[]){
    int minimaxdepth;
    try{
        minimaxdepth = (argc > 1 ? std::stoi(argv[1]) : 11);
    }catch(...){std::cout << ("Invalid depth option, using default=11\n");}
    
    board.print_board();

#ifdef __EMSCRIPTEN__
emscripten_set_main_loop(play, 60, 1);
#else 
    while(true){
        play();
    }
#endif
    
}
