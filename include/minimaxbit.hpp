#ifndef MINIMAXBIT_HPP
#define MINIMAXBIT_HPP

#include <memory>
#include <algorithm>

#include "bitboard.hpp"
#include "ltable.hpp"

struct minmax_ret{
    int column;
    int score;
};

#define ai yellow
#define human red


class MiniMaxBit{
    private:
    const int search_order[7] = {3,2,4,1,5,0,6};
    const int _depth;

    public:
    MiniMaxBit(int depth_t) : _depth(depth_t){};

    constexpr int getdepth(){
        return _depth;
    }

    minmax_ret minimax(const std::unique_ptr<BitBoard>& board, LookupTable* ltable, bool maximizing, int depth, int alpha, int beta){

        //leaf node conditions
        if(depth == 0)
            return ((minmax_ret){.column =  -1, .score = board->score(ai)/*ltable->consult(board->self())*/});
        if(board->isdraw())
            return(((minmax_ret){.column = -1, .score = 0}));
        if(board->iswin(ai))
            return ((minmax_ret){.column =  -1, .score = WIN - (100000000 * (_depth - depth))});
        if(board->iswin(human))
            return ((minmax_ret){.column =  -1, .score = LOSS});

        minmax_ret best_move({-1, (maximizing ? INT32_MIN : INT32_MAX)}), temp_ret;

        std::vector<std::unique_ptr<BitBoard>> newboards;
        newboards.reserve(7);

        for(int i = 0; i < 7; i++){ //for every potential legal move 

            newboards.push_back(std::make_unique<BitBoard>(*board)); 
            if(newboards[i]->place_token(search_order[i], (maximizing ? ai : human))){
                temp_ret = (minmax_ret){search_order[i], minimax(newboards[i], ltable, !maximizing, depth - 1, alpha, beta).score};
                if(maximizing){
                    best_move = (temp_ret.score > best_move.score ? temp_ret : best_move);
                    alpha = std::max(alpha, best_move.score);
                    if(alpha >= beta) break;
                }else{
                    best_move = (temp_ret.score < best_move.score ? temp_ret : best_move);
                    beta = std::min(beta, best_move.score);
                    if(beta <= alpha) break;
                }
            }
        }
        return best_move;
    }
    
};

#endif