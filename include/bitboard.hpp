#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <array>

#include "colours.hpp"

enum colour{
    yellow = 0 ,
    red,
    none
};

#define top_row 5
#define other_player(a) (1 - a)

#define WIN INT32_MAX
#define LOSS INT32_MIN

class BitBoard{

    private:
    
    std::array<uint64_t, 2> board;

    

    /*
    Board bits below:

        * 
        * * * * * * * 
        * * * * * * * 
        * * * * * * * 
    5   0 0 0 0 0 0 0    -->   **********************0000000000000000000000000000000000000000000000000 
    4   0 0 0 0 0 0 0 
    3   0 0 0 0 0 0 0 
    2   0 0 0 0 0 0 0 
    1   0 0 0 0 0 0 0 
    0   0 0 0 0 0 0 0 

        0 1 2 3 4 5 6

    (0 th bit is bottom left)

    */
    public:

    [[nodiscard]] constexpr uint64_t all_tokens() const {
        return board[yellow] | board[red];
    }

    [[nodiscard]] constexpr uint64_t all_empty() const {
        return ~all_tokens();
    }

    //These functions return a group of 4 tokens in the indicated position and orientation, as well as other masks used for evaluation
    static inline constexpr uint64_t row4_mask(int row, int left_col){
        assert(left_col < 4);
        return ((((uint64_t)0xF) << left_col) << (7 * row));
    }

    static inline constexpr uint64_t col4_mask(int bottom_row, int col){
        assert(bottom_row < 3);
        return ((((uint64_t)0x204081) << col) << (7 * bottom_row));
    }

    static inline constexpr uint64_t right_diag_mask(int bottom_row, int bottom_col){
        assert(bottom_row < 3 && bottom_col < 4);
        return ((((uint64_t)0x1010101) << bottom_col) << (7 * bottom_row));
    }

    static inline constexpr uint64_t left_diag_mask(int bottom_row, int bottom_col){
        assert(bottom_row < 3 && bottom_col > 2 && bottom_col < 7);
        return ((((uint64_t)0x41041) << bottom_col) << (7 * bottom_row));
    }

    static inline constexpr uint64_t token_at_mask(int row, int col){
        assert(row < 6 && col < 7);
        return (((uint64_t)0x1) << (7 * row + col));
    }


    static inline constexpr uint64_t row_mask(int row){
        assert(row < 6);
        return (static_cast<uint64_t>(0x7f) << (7 * row));
    }

    static inline constexpr uint64_t col_mask(int col){
        assert(col < 7);
        return (static_cast<uint64_t>(0x810204081) << col);
    }

    static inline constexpr uint64_t square_mask(int center_row, int center_col){
        assert(center_row < top_row && center_row > 0 && center_col < 6 && center_col > 0);
        return (static_cast<uint64_t>(0x1C387) << (7 * (center_row - 1) + center_col - 1));
    }

    static inline constexpr uint64_t x_mask(int center_row, int center_col){
        assert(center_row < top_row && center_row > 0 && center_col < 6 && center_col > 0);
        return (static_cast<uint64_t>(0x14105) << (7 * (center_row - 1) + center_col - 1));
    }

    static inline constexpr uint64_t t_mask(int center_row, int center_col){
        assert(center_row < top_row && center_row > 0 && center_col < 6 && center_col > 0);
        return (static_cast<uint64_t>(0x8382) << (7 * (center_row - 1) + center_col - 1));
    }


    //game utility functions

    bool place_token(const int column, const colour c){
        if(!(token_at_mask(top_row, column) & all_tokens())){
            int i = 5;

            while(--i >= 0 && (token_at_mask(i, column) & all_tokens()) == 0) {}

            board[c] |= token_at_mask(i + 1, column);
            return true;
        }
        return false;
    }

    [[nodiscard]] bool is_legal_move(int column) const
    {
        return (column >= 0 && column < 7) && (!(all_tokens() & token_at_mask(5, column)));
    }
    
    BitBoard()
    : board({0,0})
    {}

    BitBoard(uint64_t _yellow, uint64_t _red)
    : board({_yellow, _red})
    {}

    BitBoard(const BitBoard& old_board, const int new_move_col, const colour to_play)
    : board(old_board.board)
    {
        this->place_token(new_move_col, to_play);
    }

    std::array<uint64_t, 2>& self(){
        return board;
    }
    
    [[nodiscard]] bool isdraw() const{ //must call this AFTER iswin()!!!
        return ((all_tokens() & row_mask(5)) == row_mask(5));
    }
    
    [[nodiscard]] bool iswin(colour player) const { //for loops placed in order of frequency: games are more often won with rows/diags than columns
        for(int i = 0; i < 6; i++){ //iterate over all possible rows
            if(board[player] & row_mask(i)){ //check if tokens in row/col to speed up
                for(int j = 0; j < 4; j++){
                    if((board[player] & row4_mask(i, j)) == row4_mask(i, j))
                        return true;
                }
            }
        }
        for(int i = 0; i < 3; i++){//iterate over all possible diagonals
            for(int j = 0; j < 4; j++){
                if((board[player] & right_diag_mask(i, j)) == right_diag_mask(i, j) || (board[player] & left_diag_mask(i, j + 3)) == left_diag_mask(i, j + 3))
                    return true;
            }
        }
        for(int j = 0; j < 7; j++){//iterate over all possible columns
            if(board[player] & col_mask(j)){    
                for(int i = 0; i < 3; i++){
                        if((board[player] & col4_mask(i, j)) == col4_mask(i, j))
                            return true;
                }
            }
        }

        return false;
    }

    [[nodiscard]] int score(colour player) const { //always returns score relative to yellow (ai) player.
        int score(0);
        for(int i = 1; i < 4; i+=2){
            for(int j = 1; j < 6; j+=2){
                if(all_tokens() & square_mask(i, j)){

                    score += 
                        (
                        std::popcount<uint64_t>(board[player] & square_mask(i, j)) * 
                        std::popcount(board[player] & x_mask(i, j)) +
                        std::popcount(board[player] & t_mask(i, j))
                        ) 
                        -
                        (
                        std::popcount<uint64_t>(board[other_player(player)] & square_mask(i, j)) *
                        std::popcount(board[other_player(player)] & x_mask(i, j)) +
                        std::popcount(board[other_player(player)] & t_mask(i, j))
                        );
                }
                
            }
        }
        return score;
    }

    constexpr static int score(std::array<uint64_t, 2> someboard, colour player){
        assert(player != none);
        int score(0);
        for(int i = 1; i < 4; i+=2){
            for(int j = 1; j < 6; j+=2){
                if((someboard[0] | someboard[1]) & square_mask(i, j)){

                    score += (std::popcount<uint64_t>(someboard[player] & square_mask(i, j)) + 
                        std::popcount(someboard[player] & x_mask(i, j)) +
                        std::popcount(someboard[player] & t_mask(i, j)));

                    score -= (std::popcount<uint64_t>(someboard[other_player(player)] & square_mask(i, j)) + 
                        std::popcount(someboard[other_player(player)] & x_mask(i, j)) + 
                        std::popcount(someboard[other_player(player)] & t_mask(i, j)));
                }
                
            }
        }
        return score;
    }

    void print_board() const {
        for(int i = top_row; i >= 0; i--){

            std::cout << i << "  ";

            for(int j = 0; j < 7; j++){
                std::cout << (((board[yellow] >> (7 * i + j)) & (uint64_t)0b1) ? BOLD(FYEL("Y|")) : 
                    (((board[red] >> (7 * i + j)) & (uint64_t)0b1) ? BOLD(FRED("R|")) : BOLD(FWHT("_|"))));

            }
            std::cout << "\n";
        }
        std::cout << "\n   ";

        for(int i = 0; i < 7; i++){
            std::cout << i + 1 << " ";
        }

        std::cout << std::endl;
    }

    static void print_bitboard(uint64_t board) {
        for (int i = top_row; i >= 0; i--){
            for(int j = 0; j < 7; j++){
                std::cout << ((board >> (7 * i + j)) & (uint64_t)0b1);
            }std::cout << "\n";
        }std::cout << std::endl;
    }

};

#endif
