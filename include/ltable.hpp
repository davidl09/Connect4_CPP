#ifndef LTABLE_HPP
#define LTABLE_HPP

#include <map>
#include <cstdint>

#include "bitboard.hpp"

class LookupTable{
    private:
    std::map<std::array<uint64_t, 2>, int> table;

    public:
    int consult(std::array<uint64_t, 2> board){
        if(table[board])
    }
    
};

#endif