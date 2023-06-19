#include "board.hpp"
#include <algorithm>

#define ai yellow
#define human red


struct minimax_ret{
    int score;
    int column;
};

class MiniMax{
    public:
    minimax_ret minimax(const std::unique_ptr<Board<6, 7>>& board, bool maximizing, int depth, int alpha, int beta){
        minimax_ret current = {board->board_score(ai), INT32_MAX};
        auto isdraw = [](Board<6, 7>& b){for(int i = 0; i < b.width(); i++) if(b.square_at(0, i) == 0) return false; return true;};

        if(depth == 0 || current.score == INT32_MAX || current.score == INT32_MIN || isdraw(*board)){
            return current; //intmax since column that led to this move is unknown in the leaf node
        }
        
        std::array<minimax_ret, 7> moves; //must be properly templated later
        
        for(int i = 0; i < 7; i++){
            std::unique_ptr<Board<6,7>> new_board = std::make_unique<Board<6, 7>>(board->board_t());
            if(new_board->add_token((maximizing ? ai : human), i)){
                moves[i] = minimax(new_board, !maximizing, depth - 1, alpha, beta);
                //add alpha/beta code here later
                moves[i].column = i;    
            }
            else moves[i] = {INT32_MIN, -1};
        }

        std::sort(moves.begin(), moves.end(), [](minimax_ret a, minimax_ret b){return a.score > b.score;});
        return moves[(maximizing ? 0 : 6)];
 
    }
};