
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

    MiniMaxBit algo;
    minmax_ret score_col;// = algo.minimax(b, &table, true, 9, INT32_MIN, INT32_MAX);

    b->print_board();


    int move;
    while(true){
        std::cout << "Enter your move\n";
        std::cin >> move;
        b->place_token(move, red);
        score_col = algo.minimax(b, &table, true, maxdepth, INT32_MIN, INT32_MAX);
        std::cout << "\nScore: " << score_col.score << "\nColumn: " << score_col.column << "\n";
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