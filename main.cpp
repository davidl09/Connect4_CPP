
//#include "minimax.hpp"
#include "bitboard.hpp"
#include "ltable.hpp"

extern "C"
{
    
}

int main(){
    BitBoard b;
    //BitBoard::print_bitboard(b.square_mask(4, 5));
/*
    b.place_token(2, yellow);
    b.place_token(4, red);
    b.place_token(1, yellow);
    b.place_token(2, red);
    b.place_token(6, yellow);
*/  b.place_token(3, red);

    b.place_token(0, yellow);
    b.place_token(6, red);
    LookupTable table;

    int score = table.consult(b.self());


    b.print_board();

    std::cout << "Score: " << b.score(yellow) << "\nTable score: " << score << "\n";
    //b.iswin(red) ? std::cout << "Win\n" : std::cout << "No win\n";
    /*
    std::unique_ptr<Board<6, 7>> ptr = std::make_unique<Board<6, 7>>();
    MiniMax m;
    minimax_ret r = m.minimax(ptr, true, 7, INT32_MIN, INT32_MAX);
    std::cout << "Score: " << r.score << "\n" << "Column: " << r.column;
    */
}