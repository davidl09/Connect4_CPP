#include <memory>

#include "bitboard.hpp"

#define ai yellow
#define human red

class MinimaxTreeNode
{
    private:
        BitBoard state;
        int score;
        const int player_turn;
        const int depth;
        std::vector<std::unique_ptr<MinimaxTreeNode>> child_nodes;

        int score()
        {
            return score;
        }

        bool is_terminal_node()
        {
            return state.isdraw() || state.iswin(ai) || state.iswin(human);
        }

        bool is_leaf_node()
        {
            return depth <= 0;
        }
/* need to add method to update depth
        void add_node()
        {
            if(is_leaf_node() && !is_terminal_node())
            {
                for(int i = 0; i < 7; ++i)
                {
                    if(state.is_legal_move(i))
                        child_nodes.emplace_back(std::make_unique<MinimaxTreeNode>(state, other_player(to_play), i, depth - 1));
                } 
            }
        }
*/
    public:
        MinimaxTreeNode(BitBoard& board, colour to_play, int column_to_play, int _depth) : player_turn(to_play), depth(_depth)
        {
            state = board;
            state.place_token(column_to_play, to_play);
            if(state.iswin(ai))
                score = WIN;
            else if(state.iswin(human))
                score = LOSS;
            else score = state.score(ai);

            if(!(state.isdraw() || state.iswin(ai) || state.iswin(human) || depth == 0))
            {
                for(int i = 0; i < 7; ++i)
                {
                    if(state.is_legal_move(i))
                        child_nodes.emplace_back(std::make_unique<MinimaxTreeNode>(state, other_player(to_play), i, depth - 1));
                } 
            }
            
        }

        MinimaxTreeNode& max_or_min_child_node()
        {
            for()
        }
};

class MinimaxTree
{
    private:
        const int depth;

        void build(int depth );

    public:
        MinimaxTree(int _depth) : depth(_depth)
        {

        }


};