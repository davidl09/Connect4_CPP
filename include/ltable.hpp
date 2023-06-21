#ifndef LTABLE_HPP
#define LTABLE_HPP

#include <map>
#include <memory>

#include "bitboard.hpp"

class LookupTable{
    private:
    std::unique_ptr<std::map<std::pair<uint64_t, uint64_t>, int>> table;

    public:
    LookupTable() : table(std::make_unique<std::map<std::pair<uint64_t, uint64_t>, int>>()) {}

    int consult(std::array<uint64_t, 2> board){
        std::pair<uint64_t, uint64_t> temp = std::make_pair(board[yellow], board[red]);
        int ret = BitBoard::score(board, yellow);

        if(!(*table)[temp]){
            table->insert(std::make_pair(temp, ret));
        }
        return ret; //faster than looking up value again and omitting local var
    }    

};

#endif