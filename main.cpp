
#include "board.hpp"

extern "C"
{
    
}

int main(){
    Board<6, 7> b;
    for(int i = 0; i < 2; i++){
        b.add_token(yellow, 4);
        b.add_token(red, 2);
        b.add_token(red, 2);
    }

    std::cout << "Original: \n";
    b.print_debug();

    auto a = b.board_copy_ptr();

    std::cout << "Copied: \n";
    a->print_debug();

    std::cout << b.iswin() << std::endl;
}
