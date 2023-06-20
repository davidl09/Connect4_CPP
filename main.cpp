
//#include "minimax.hpp"
#include "bitboard.hpp"

extern "C"
{
    
}

int main(){
    BitBoard b;
    b.print_board();
    b.place_token(4, red);
    b.place_token(4, red);
    b.place_token(4, red);
    //b.place_token(4, red);


    b.print_board();
    b.iswin(red) ? std::cout << "Win\n" : std::cout << "No win\n";
    /*
    std::unique_ptr<Board<6, 7>> ptr = std::make_unique<Board<6, 7>>();
    MiniMax m;
    minimax_ret r = m.minimax(ptr, true, 7, INT32_MIN, INT32_MAX);
    std::cout << "Score: " << r.score << "\n" << "Column: " << r.column;
    */
}