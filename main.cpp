
#include "bitboard.hpp"
#include "minimaxbit.hpp"

int main(int argc, char* argv[]){
    BitBoard b;
    int minimaxdepth;
    try{
        minimaxdepth = (argc > 1 ? std::stoi(argv[1]) : 11);
    }catch(...){std::cout << ("Invalid depth option, using default=11\n");}

    MiniMaxBit algo = MiniMaxBit(minimaxdepth);
    
    b.print_board();

    int move;
    while(true){
        
        std::cout << "Enter your move\n";
        std::cin >> move;

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
    
}