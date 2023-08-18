#ifndef MINIMAXBIT_HPP
#define MINIMAXBIT_HPP

#include <memory>
#include <algorithm>
#include <thread>
#include <atomic>

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

    int best_move(const std::unique_ptr<BitBoard>& board){
        std::vector<minmax_ret> moves;
        moves.reserve(7);

        std::vector<std::thread> move_threads;
        move_threads.reserve(7);

        for(int i = 0; i < 7; i++){
            moves.push_back((minmax_ret){search_order[i], INT32_MIN});

            move_threads.push_back(std::thread(threaded_minimax, board->self(), &(moves[i]), this->_depth));
        }

        for(int i = 0; i < 7; i++){

        }

    }
/*
    static void threaded_minimax(uint64_t board[2], minmax_ret* retval, const int depth){
        auto ptr = std::make_unique<BitBoard>(board);
        *retval = MiniMaxBit(depth).minimax(ptr, nullptr, false, depth - 1, INT32_MIN, INT32_MAX);
    }
*/
    int minimax(BitBoard& board, LookupTable* ltable, bool maximizing, int depth, int alpha, int beta){

        //leaf node conditions
        if(depth == 0)
            return board.score(ai);
        if(board.isdraw())
            return 0;
        if(board.iswin(ai))
            return WIN - (100000000 * (_depth - depth));
        if(board.iswin(human))
            return LOSS;

        std::vector<int> newboards;
        newboards.reserve(7);

        for(int i = 0; i < 7; i++){ //for every potential legal move 
        if(board.is_legal_move(i))
        {
            newboards.emplace_back(minimax())
        }
        /*
            newboards.emplace_back(BitBoard(board)); 
            if(newboards[i].place_token(search_order[i], (maximizing ? ai : human))){
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
            }*/
        }
        return best_move;
    }
    
};

#endif