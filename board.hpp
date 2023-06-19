#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <stdexcept>
#include <array>
#include <iostream>
#include <memory>
#include <limits>

enum square_state{
    empty = 0,
    yellow,
    red
};

/*
template<int _rows>
class Column{
    public:
    square& operator[] (int row) {return this->column.at(row);}
    private:
    std::array<_rows, square> column;
}; */ //nice, but slower. use custom at() method on board instead

template<int _rows, int _columns>
class Board{

    private:
    const int rows = _rows;
    const int columns = _columns;
    std::array<square_state, (_rows * _columns)> board; //IMPORTANT! Board is internally indexed [column][row], unlike most 2D arrays. use custom .at() method
    
    
    public:
    Board(){
        this->board = {empty};
    }

    Board(std::array<square_state, _rows * _columns>& new_arr){
        this->board = new_arr;
    }

    Board(std::array<square_state, _rows * _columns>&& new_arr_ref){
        this->board = new_arr_ref;
    }

    Board(Board&& b){
        this->board = b.board;
        
    }

    constexpr const int& width(){
        return columns;
    }

    constexpr const int& height(){
        return rows;
    }

    const std::unique_ptr<Board>& board_copy_ptr(){
        //std::unique_ptr<Board<_rows, _columns>> ptr(new Board(this->board));
        return std::make_unique<Board<_rows, _columns>>(this->board);
    }

    Board board_copy(){
        Board temp(this->board);
        return temp;
    }

    Board board_t(){
        return board;
    }

    inline const square_state& square_at(const int row, const int column){
        return board.at(column * rows + row); //at() does index checking
    }

    inline const square_state& square_at(const int index){
        return board.at(index);
    }

    /*
    Raw Board indecies below:

    0 6 12 18 24 30 36
    1 7 
    2
    3
    4
    5

    */

    bool add_token(square_state c, int column){
        for(int i = rows - 1; i >= 0; i--){ //counting from the bottom up
            if(!square_at(i, column)){
                board[column * rows + i] = c; //bounds have been checked by square_at() before this unchecked access so no 
                return true;
            }
        }
        return false;
    }

    int pop_count_c(int column){
        for(int i = 0; i < rows; i++){
            if(square_at(i, column)){
                return 6 - i;
            }
        }
        return 6;
    }

    inline int evaluate_window(int counts[3], square_state player){
        if(counts[3-player] == 4) return INT32_MIN;
        if(counts[player] == 4) return INT32_MAX;
        if(counts[empty] == 4) return 0;
        return 100 * counts[player] - 100 * counts[3 - player] + (counts[empty] == 0 ? -100 : 100);
    }

    int board_score(square_state player){
        int score = 0;
        int counts[3] = {0}, temp = 0;
        for (int i = 0; i < rows; ++i) { //check rows
            for (int j = 0; j < columns - 3; ++j) {

                for(int k = 0; k < 4; k++){
                    counts[square_at(i, j + k)]++;
                }

                if((temp = evaluate_window(counts, player)) == INT32_MAX) return temp; //check for win/loss
                if(temp == INT32_MIN) return temp;
                score += temp;
                for(int l = 0; l < 3; l++) counts[l] = 0;
            }
        }

        for (int i = 0; i < rows - 3; ++i) { //check columns
            for (int j = 0; j < columns; ++j) {

                for(int k = 0; k < 4; k++){
                    counts[square_at(i + k, j)]++;
                }

                if((temp = evaluate_window(counts, player)) == INT32_MAX) return temp; //check for win/loss
                if(temp == INT32_MIN) return temp;
                score += temp;
                for(int l = 0; l < 3; l++) counts[l] = 0;
            }
        }

        for (int i = 0; i < rows - 3; ++i) { //check downward diagonals
            for (int j = 0; j < columns - 3; ++j) {
                
                for(int k = 0; k < 4; k++){
                    counts[square_at(i + k, j + k)]++;
                }

                if((temp = evaluate_window(counts, player)) == INT32_MAX) return temp; //check for win/loss
                if(temp == INT32_MIN) return temp;
                score += temp;
                for(int l = 0; l < 3; l++) counts[l] = 0;
            }
        }

        for (int i = 3; i < rows; ++i) { //check upward diagonals
            for (int j = 0; j < columns - 3; ++j) {

                for(int k = 0; k < 4; k++){
                    counts[square_at(i - k, j + k)]++;
                }

                if((temp = evaluate_window(counts, player)) == INT32_MAX) return temp; //check for win/loss
                if(temp == INT32_MIN) return temp;
                score += temp;
                for(int l = 0; l < 3; l++) counts[l] = 0;
            }
        }
        return score;
    }

    void print_debug(){
        std::cout << "\n\n\n\n\n\n";
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                switch(square_at(i, j)){
                    case empty:
                    std::cout << "O ";
                    break;

                    case yellow:
                    std::cout << "Y ";
                    break;

                    case red:
                    std::cout << "R ";
                    break;
                }
            }
            std::cout << "\n";
        }
    }


/*
    struct IterSquares{

        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = char;
        using pointer           = char*;  
        using reference         = char&;

        IterSquares(pointer ptr) : m_ptr(ptr) {}
        
        reference operator* () const {return *m_ptr;}
        pointer operator-> () {return m_ptr;}


        IterSquares& operator++() {m_ptr++; return *this;}
        IterSquares operator++(int) {IterSquares temp = *this; ++(*this); return temp;}

        friend bool operator== (const IterSquares& a, const IterSquares& b){return a.m_ptr == b.m_ptr;}
        friend bool operator!= (const IterSquares& a, const IterSquares& b){return a.m_ptr != b.m_ptr;}
        
        private:
        pointer m_ptr;
    };
*/
};

#endif