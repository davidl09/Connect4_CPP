#ifndef MINIMAXBIT_HPP
#define MINIMAXBIT_HPP

#include <algorithm>

#include "bitboard.hpp"

#define ai yellow
#define human red


class MiniMaxBit{
    constexpr static std::array search_order = {3,2,4,1,5,0,6};
    int _depth;

    public:
    explicit constexpr MiniMaxBit(int depth_t = 11) : _depth(depth_t){};

    [[nodiscard]] constexpr int getdepth() const{
        return _depth;
    }

    int best_move(BitBoard& board){
        std::vector<std::pair<int, int>> move_score_pairs;
        for(const int i : search_order)
        {
            if(board.is_legal_move(i))
            {
                move_score_pairs.emplace_back(
                    i,
                        __minimax(BitBoard(board, i, yellow), false, _depth - 1, INT32_MIN, INT32_MAX)
                      //this minimax function gets a board with ai token placed last and must therefore seek to minimize the score (it's the human's  turn)
                );      //nullptr since lookup table is not being used (worsens performance according to benchmark)
                //assuming always looking for best move for ai (yellow)
            }
        }

        auto comp = [](const std::pair<int, int> a, const std::pair<int, int> b){return a.second < b.second;};
        return std::ranges::max_element(move_score_pairs, comp)->first;
    }
    
    int __minimax(BitBoard&& board, bool maximizing, int depth, int alpha, int beta){

        //leaf node conditions
        if(depth == 0)
            return board.score(ai);
        if(board.isdraw())
            return 0;
        if(board.iswin(ai))
            return WIN - (100000000 * (_depth - depth)); //favors 'shallower' wins (sooner)
        if(board.iswin(human))
            return LOSS;

        std::vector<int> newboards;
        newboards.reserve(7);

        for(int i = 0; i < 7; i++){ //for every potential legal move 
            if(board.is_legal_move(i))
            {
                newboards.emplace_back(__minimax(BitBoard(board, search_order[i], static_cast<colour>(!maximizing)), !maximizing, depth - 1, alpha, beta));
                if(maximizing)
                {
                    alpha = std::max(newboards.back(), alpha);
                    if(alpha >= beta) break;
                }
                else
                {
                    beta = std::min(newboards.back(), beta);
                    if(beta <= alpha) break;
                }
            }
        }

        if(maximizing)
            return *std::ranges::max_element(newboards);
        return *std::ranges::min_element(newboards);
    }
    
};

#endif