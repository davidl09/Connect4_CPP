
#include "minimax.hpp"

extern "C"
{
    
}

int main(){
    std::unique_ptr<Board<6, 7>> ptr = std::make_unique<Board<6, 7>>();
    MiniMax m;
    m.minimax(ptr, true, 1, INT32_MIN, INT32_MAX);
}
