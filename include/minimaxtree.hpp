#include <cmath>
#include <algorithm>

#include "bitboard.hpp"

#define ai yellow
#define human red

class MinimaxTreeNode
{
    private:
        BitBoard state;
        const int score;
        const int player_turn;
        int depth;
        std::vector<MinimaxTreeNode> child_nodes;

        constexpr int get_score()
        {
            return score;
        }

        BitBoard get_state() //pass by copy to avoid modifying
        {
            return state;
        }

        bool is_terminal_node()
        {
            return state.isdraw() || state.iswin(ai) || state.iswin(human);
        }

        bool is_leaf_node()
        {
            return depth <= 0;
        }

        void add_layer()
        {
            if(!(is_leaf_node() || is_terminal_node()))
            {
                for(int i = 0; i < 7; ++i)
                {
                    if(state.is_legal_move(i))
                        child_nodes.emplace_back(
                            MinimaxTreeNode(
                                BitBoard(state, i, static_cast<colour>(player_turn)), 
                                static_cast<colour>(other_player(player_turn)), depth - 1
                                )
                            );
                } 
            }
        }

        int where_last_placed(BitBoard& board) //will break if more than one token has been placed between state and provided board (argument).
        {
            auto diff = board.all_tokens() ^ this->state.all_tokens(); //only bit set to 1 should be where new token was placed.
            return static_cast<int>(std::floor(std::log2(diff))) % 7; //board is 7 slots wide, so get the position of the bit and take % 7 to get column pos.
        }

        int where_last_placed(BitBoard&& board) //will break if more than one token has been placed between state and provided board (argument).
        {
            auto diff = board.all_tokens() ^ this->state.all_tokens(); //only bit set to 1 should be where new token was placed.
            return static_cast<int>(std::floor(std::log2(diff))) % 7; //board is 7 slots wide, so get the position of the bit and take % 7 to get column pos.
        }

    public:
        MinimaxTreeNode(BitBoard board, colour to_play, int _depth) 
        : state(board), 
        score(board.score(ai)),
        player_turn(to_play), 
        depth(_depth)
        {
            add_layer();
        }

        MinimaxTreeNode& best_node(colour player) //need to rewrite to recurse across entire tree
        {
            /*auto is_second_last = true;
            for(auto & node : child_nodes)
            {
                if(node.is_terminal())
            }*/
            if(!(is_leaf_node() || is_terminal_node()))
            {
                auto comp = [this](MinimaxTreeNode& a, MinimaxTreeNode& b)
                    {
                        return (player_turn == ai ? a.get_score() < b.get_score() : a.get_score() > b.get_score());
                    };
                return *std::max_element(child_nodes.begin(), child_nodes.end(), comp);
            }
        }

        void increase_depth(int increase)
        {
            depth += increase;
            if(!(is_leaf_node() || is_terminal_node()))
            {
                if(child_nodes.size() == 0)
                    add_layer();
                else
                {
                    for(auto& node : child_nodes)
                    {
                        node.increase_depth(increase);
                    }
                }
            }
        }
};
/*
class MinimaxTree
{
    private:
        const int depth;
        MinimaxTreeNode root_node;

    public:
    
        MinimaxTree(BitBoard& start_board, int _depth)
         : depth(_depth), root_node(MinimaxTreeNode(start_board, yellow, ))
        {

        }


};*/