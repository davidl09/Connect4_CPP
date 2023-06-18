#ifndef BOARD_HPP_INCLUDE
#define BOARD_HPP_INCLUDE

#include <stdexcept>
#include <array>
#include <iostream>
#include <memory>

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
    public:
    Board(){
        this->board = {empty};
    }

    Board(std::array<square_state, _rows * _columns> new_arr){
        this->board = new_arr;
    }

    std::unique_ptr<Board> board_copy_ptr(){
        std::unique_ptr<Board<_rows, _columns>> ptr(new Board(this->board));
        return ptr;
    }

    Board board_copy(){
        Board temp(this->board);
        return temp;
    }

    inline const square_state& square_at(const int row, const int column){
        return board.at(column * rows + row); //at() does index checking
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

    square_state iswin(){ //need to speed this up with more efficient search!!!
        for (int i = 0; i < rows; ++i) { //check rows
            for (int j = 0; j < columns - 3; ++j) {
                if (square_at(i, j)  == square_at(i, j + 1)  && square_at(i, j + 1)  == square_at(i, j + 2)  && square_at(i, j + 2)  == square_at(i, j + 3)  && square_at(i, j)  != 0) {
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 0; i < rows - 3; ++i) { //check columns
            for (int j = 0; j < columns; ++j) {
                if (square_at(i, j)  == square_at(i + 1, j)  && square_at(i+1, j)  == square_at(i + 2, j)  && square_at(i + 2, j)  == square_at(i + 3, j)  && square_at(i, j)  != 0) {
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 0; i < rows - 3; ++i) { //check downward diagonals
            for (int j = 0; j < columns - 3; ++j) {
                if(square_at(i, j)  == square_at(i+1, j+1)  && square_at(i+1, j+1)  == square_at(i+2, j+2)  && square_at(i+2, j+2)  == square_at(i+3, j+3)  && square_at(i, j)  != 0){
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 3; i < rows; ++i) { //check upward diagonals
            for (int j = 0; j < columns - 3; ++j) {
                if(square_at(i, j)  == square_at(i-1, j+1)  && square_at(i-1, j+1)  == square_at(i-2, j+2)  && square_at(i-2, j+2)  == square_at(i-3, j+3)  && square_at(i, j)  != 0){
                    return square_at(i, j) ;
                }
            }
        }
        return empty;
    }

    int pop_count_c(int column){
        for(int i = 0; i < rows; i++){
            if(square_at(i, column)){
                return 6 - i;
            }
        }
        return 6;
    }

    int board_score(square_state player){
        long long score = 0;
        //square_state temp, temp_l[4];

        for(int i = 0; i < columns; i++){
            score += 20 * pop_count_c(i);
            for(int j = 0; j < rows; j++){
                score -= (square_at(i, j) == 3 - player ? 20 : 0);
            } //to be finished later
        }

        //verticals
        
        //down right diagonals
        

        /*
        for(int i = 1; i < rows - 1; i+=2){
            for(int j = 1; j < columns - 1; j++){
                for(int k = -1; k < 2; k++){
                    temp_l[0] += ((temp = square_at(i + k, j)) == player ? 20 : (temp == 0 ? 0 : -20)); //check vertical squares

                    temp_l[1] += ((temp = square_at(i, j + k)) == player ? 20 : (temp == 0 ? 0 : -20)); //check horizontal squares

                    temp_l[2] += ((temp = square_at(i + k, j + k)) == player ? 20 : (temp == 0 ? 0 : -20)); //check right diagonal squares

                    temp_l[3] += ((temp = square_at(i - k, j + k)) == player ? 20 : (temp == 0 ? 0 : -20)); //check left diagonal squares
                }
                for(int k = 0; k < 4; ++k){
                    if(temp_l[k] >= 60){
                        switch(k){
                            case 0:

                        }
                    }
                    temp_l[k] = (temp_l[k] >= 60 ? 200 : temp_l[k] >= 40 ? 150 : temp_l[k]);
                    score += temp_l[k];
                    temp_l[k] = 0;
                }
            }
        }
        return score;*/
    }

    /*
    //always returns a score positively correlated with how much player_ is winning, last position in the array is the player receiving positive scores for winning positions
    long long int window_score(square_state window[5]){

    }


    long long int board_score(square_state player_){
        long long int score = 0;
        for (int i = 0; i < rows; ++i) { //check rows
            for (int j = 0; j < columns - 3; ++j) {
                if (square_at(i, j)  == square_at(i, j + 1)  && square_at(i, j + 1)  == square_at(i, j + 2)  && square_at(i, j + 2)  == square_at(i, j + 3)  && square_at(i, j)  != 0) {
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 0; i < rows - 3; ++i) { //check columns
            for (int j = 0; j < columns; ++j) {
                if (square_at(i, j)  == square_at(i + 1, j)  && square_at(i+1, j)  == square_at(i + 2, j)  && square_at(i + 2, j)  == square_at(i + 3, j)  && square_at(i, j)  != 0) {
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 0; i < rows - 3; ++i) { //check downward diagonals
            for (int j = 0; j < columns - 3; ++j) {
                if(square_at(i, j)  == square_at(i+1, j+1)  && square_at(i+1, j+1)  == square_at(i+2, j+2)  && square_at(i+2, j+2)  == square_at(i+3, j+3)  && square_at(i, j)  != 0){
                    return square_at(i, j) ;
                }
            }
        }
        for (int i = 3; i < rows; ++i) { //check upward diagonals
            for (int j = 0; j < columns - 3; ++j) {
                if(square_at(i, j)  == square_at(i-1, j+1)  && square_at(i-1, j+1)  == square_at(i-2, j+2)  && square_at(i-2, j+2)  == square_at(i-3, j+3)  && square_at(i, j)  != 0){
                    return square_at(i, j) ;
                }
            }
        }

    }*/

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
    

    private:
    const int rows = _rows;
    const int columns = _columns;
    std::array<square_state, (_rows * _columns)> board; //IMPORTANT! Board is internally indexed [column][row], unlike most 2D arrays. use custom .at() method

};

#endif