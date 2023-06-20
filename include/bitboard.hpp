#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <cassert>
#include <cstdint>
#include <iostream>
#include <array>

enum colour{
    yellow = 0 ,
    red,
    none
};


class BitBoard{

    private:
    
    std::array<uint64_t, 2> board;

    #define top_row 5

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

    const constexpr uint64_t all_tokens(){
        return board[yellow] | board[red];
    }

    //These functions return a group of 4 tokens in the indicated position and orientation
    static const constexpr uint64_t row4_mask(int row, int left_col){
        assert(left_col < 4);
        return ((((uint64_t)0xF) << left_col) << (7 * row));
    }

    static const constexpr uint64_t col4_mask(int bottom_row, int col){
        assert(bottom_row < 3);
        return ((((uint64_t)0x204081) << col) << (7 * bottom_row));
    }

    static const constexpr uint64_t right_diag_mask(int bottom_row, int bottom_col){
        assert(bottom_row < 3 && bottom_col < 4);
        return ((((uint64_t)0x1010101) << bottom_col) << (7 * bottom_row));
    }

    static const constexpr uint64_t left_diag_mask(int bottom_row, int bottom_col){
        assert(bottom_row < 3 && bottom_col > 2 && bottom_col < 7);
        return ((((uint64_t)0x41041) << bottom_col) << (7 * bottom_row));
    }

    static inline const constexpr uint64_t token_at_mask(int row, int col){
        assert(row < 6 && col < 7);
        return (((uint64_t)0x1) << (7 * row + col));
    }


    static const constexpr uint64_t row_mask(int row){
        assert(row < 6);
        return (((uint64_t)0x7f) << (7 * row));
    }

    static const constexpr uint64_t col_mask(int col){
        assert(col < 7);
        return (((uint64_t)0x810204081) << col);
    }


    //game utility functions

    bool place_token(const int column, const colour c){
        if((token_at_mask(top_row, column) & all_tokens()) == 0){
            int i = 5;

            while(--i >= 0 && (token_at_mask(i, column) & all_tokens()) == 0);

            board[c] |= token_at_mask(i + 1, column);
            return true;
        }
        return false;
    }
    
    BitBoard(){
        board[yellow] = 0ULL;
        board[red] = 0ULL;
    }

    BitBoard(uint64_t yellow, uint64_t red){
        board[yellow] = yellow;
        board[red] = red;
    }
    
    bool isdraw(){ //must call this AFTER iswin()!!!
        if((all_tokens() & row_mask(5)) == row_mask(5)) return true;
        return false;
    }
    
    bool iswin(colour player){
        for(int i = 0; i < 6; i++){
            if(board[player] & row_mask(i)){ //check if tokens in row/col to speed up
                for(int j = 0; j < 4; j++){
                    if((board[player] & row4_mask(i, j)) == row4_mask(i, j))
                        return true;
                }
            }
        }
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 4; j++){
                if((board[player] & right_diag_mask(i, j)) == right_diag_mask(i, j) || (board[player] & left_diag_mask(i, j + 3)) == left_diag_mask(i, j + 3))
                    return true;
            }
        }
        for(int j = 0; j < 7; j++){
            if(board[player] & col_mask(j)){    
                for(int i = 0; i < 3; i++){
                        if((board[player] & col4_mask(i, j)) == col4_mask(i, j))
                            return true;
                }
            }
        }

        return false;
    }

    int boardscore(){

    }

    const void print_board(){
        for(int i = top_row; i >= 0; i--){
            for(int j = 0; j < 7; j++){
                std::cout << ((all_tokens() >> 7 * i + j) & (uint64_t)0b1);
            }std::cout << "\n";
        }std::cout << std::endl;
    }

    static const void print_bitboard(uint64_t board){
        for(int i = top_row; i >= 0; i--){
            for(int j = 0; j < 7; j++){
                std::cout << ((board >> (7 * i + j)) & (uint64_t)0b1);
            }std::cout << "\n";
        }std::cout << std::endl;
    }

};

#endif
