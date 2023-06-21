#ifndef MINIMAXBIT_HPP
#define MINIMAXBIT_HPP

#include <memory>

#include "bitboard.hpp"
#include "ltable.hpp"

struct minmax_ret{
    int column;
    int score;
};

#define ai yellow
#define human red

class MiniMaxBit{
    public:
    minmax_ret minimax(const std::unique_ptr<BitBoard>& board, LookupTable* ltable, bool maximizing, int depth, int alpha, int beta){

        //leaf node conditions
        if(depth == 0)
            return ((minmax_ret){.column =  -1, .score = ltable->consult(board->self())});
        if(board->isdraw())
            return(((minmax_ret){.column = -1, .score = 0}));
        if(board->iswin(ai))
            return ((minmax_ret){.column =  -1, .score = WIN});
        if(board->iswin(human))
            return ((minmax_ret){.column =  -1, .score = LOSS});

        std::array<minmax_ret, 7> results;
        std::vector<std::unique_ptr<BitBoard>> newboards;
        newboards.reserve(7);
        for(int i = 0; i < 7; i++){
            newboards.push_back(std::make_unique<BitBoard>(board->self()[0], board->self()[1])); //speed this up with copy constructor
            if(newboards[i]->place_token(i, (maximizing ? ai : human))){
                results[i] = minimax(newboards[i], ltable, !maximizing, depth - 1, alpha, beta);
            }//tbc
        }
    }
    
};

#endif