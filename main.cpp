
//#include "minimax.hpp"
#include "bitboard.hpp"
#include "ltable.hpp"
#include "minimaxbit.hpp"


int main(int argc, char* argv[]){
    std::unique_ptr<BitBoard> b(std::make_unique<BitBoard>());
    
    LookupTable table;
    int minimaxdepth;
    try{
        minimaxdepth = (argc > 1 ? std::stoi(argv[1]) : 10);
    }catch(...){std::cout << ("Invalid depth option, using default=10\n");}

    MiniMaxBit algo = MiniMaxBit(minimaxdepth);
    int score_col;

    b->print_board();


    int move;
    while(true){

        std::cout << "Enter your move\n";
        std::cin >> move;

        if(move < 0 || move > 6){
            std::cout << "That was an invalid move, try again\n";
            continue;
        }

        b->place_token(move, red);
        b->print_board();

        std::cout << "AI plays...\n";
        score_col = algo.best_move(b);
        std::cout << "AI played in column: " << score_col << "\n";

        b->place_token(score_col, ai);
        b->print_board();

        if(b->iswin(ai)){
            std::cout << "AI wins!\n";
            exit(0);
        }
        if(b->iswin(human)){
            std::cout << "You win!\n";
            exit(0);
        }
        if(b->isdraw()){
            std::cout << "Draw...\n";
            exit(0);
        }
    }
    
}