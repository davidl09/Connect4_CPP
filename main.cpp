
//#include "minimax.hpp"
#include "bitboard.hpp"
#include "ltable.hpp"
#include "minimaxbit.hpp"

extern "C"
{
    
}

int main(int argc, char* argv[]){
    std::unique_ptr<BitBoard> b(std::make_unique<BitBoard>());
    
    LookupTable table;
    int minimaxdepth;
    try{
        minimaxdepth = (argc > 1 ? std::stoi(argv[1]) : 11);
    }catch(...){std::cout << ("Invalid depth option, using default=11\n");}

    MiniMaxBit algo = MiniMaxBit(minimaxdepth);
    minmax_ret score_col;

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
        score_col = algo.minimax(b, &table, true, algo.getdepth(), INT32_MIN, INT32_MAX);
        std::cout << "AI played in column: " << score_col.column << "\n";

        b->place_token(score_col.column, ai);
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