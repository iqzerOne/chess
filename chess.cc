#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>

const int rows = 8, columns = 8;

enum Figura_f {pawns,knight,bishop,rook,queen,king,kletka};

enum Color {white,black};

std::string whiteF[6] = {"♙","♘","♗","♖","♕","♔"};
std::string blackF[6] = {"♟","♞","♝","♜","♛","♚"};


class Figura{
public:

    Figura_f name;
    Color value_color;

    Figura(){}

    Figura(Figura_f name_f,Color color){
        this -> name = name_f;
        this -> value_color = color;
    }
    Figura(Figura_f name_f){
        this -> name = name_f;
    }
    Figura_f GetValue (){
        return name;
    }
    void SetValue(Figura_f number_value){
        this -> name = number_value;
    }
    Color GetColor(){
        return value_color;
    }
    void SetColor(Color color){
       this -> value_color = color;
    }
};

class Board{
public:

    Figura copy_board [columns][rows];

    int castling_left_Black = 1;
    int castling_right_Black = 1;
    int castling_left_White = 1;
    int castling_right_White = 1;

    int last_move_y, last_move_x;
    int last_move_change_y,last_move_change_x;

    Board(Figura board[columns][rows]){
        for(int i = 0; i < columns; i++){
            for(int j = 0; j < rows; j++){
                copy_board[i][j].name = board[i][j].name;
                copy_board[i][j].value_color = board[i][j].value_color;
            }
        }
    }

    Figura GetValue(int col,int row){
        if(col >= 0 && row >= 0 && col < 8 && row < 8){
            return copy_board[col][row];
        }else{
            throw std::runtime_error("out of range "+ std::to_string(col)+ " " + std::to_string(row));
        }
    }   

    void SetValue(int c_y, int c_x,int y, int x){
        if(c_y >= 0 && c_x >= 0 && c_y < 8 && c_x < 8){
            this -> copy_board[c_y][c_x].name = copy_board[y][x].name;
            this -> copy_board[c_y][c_x].value_color = copy_board[y][x].value_color;
        }else{
            throw std::runtime_error("out of range "+ std::to_string(c_y)+ " " + std::to_string(c_x));
        }
        
    }
    void SetValue_kletka(int y, int x, Figura_f value){
        this -> copy_board[y][x].name = value;
    }

};

Figura w(Figura_f value){

    Figura value_w_f(value,Color::white);

    return value_w_f;
}

Figura b(Figura_f value){

    Figura value_w_f(value,Color::black);

    return value_w_f;
}


int attention[rows][columns]{
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};


Figura empty_board[columns][rows]
{
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
};

Figura chess_board[rows][columns]
{
    {b(rook),b(knight),b(bishop),b(queen),b(king),b(bishop),b(knight),b(rook)},
    {b(pawns),b(pawns),b(pawns),b(pawns),b(pawns),b(pawns),b(pawns),b(pawns)},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {kletka,w(knight),kletka,w(bishop),kletka,w(queen),w(knight),kletka},
    {kletka,kletka,kletka,kletka,kletka,w(bishop),kletka,kletka},
    {kletka,kletka,kletka,kletka,kletka,kletka,kletka,kletka},
    {w(pawns),w(pawns),w(pawns),w(pawns),w(pawns),w(pawns),w(pawns),w(pawns)},
    {w(rook),kletka,kletka,kletka,w(king),kletka,kletka,w(rook)}
};

class Move{
public:
    int y,x;
    int change_y, change_x;

    Move(int push_y,int push_x,int push_change_y,int push_change_x){
        y = push_y;
        x = push_x;
        change_y = push_change_y;
        change_x = push_change_x;
    }

    void move_figura(Board& board){
    // Флаги для белых    
        if(board.GetValue(7,4).name == king){
            if(board.GetValue(7,0).name == rook){
                board.castling_left_White = 1;
            }else{
                board.castling_left_White = 0;
            }
            if(board.GetValue(7,7).name == rook){
                board.castling_right_White = 1;
            }else{
                board.castling_right_White = 0;
            }
        }else{
            board.castling_left_White = 0;
            board.castling_right_White = 0;
    }
    //
    //Флаги для черных
        if(board.GetValue(0,4).name == king){
            if(board.GetValue(0,0).name == rook){
                board.castling_left_Black = 1;
            }else{
                board.castling_left_Black = 0;
            }
            if(board.GetValue(0,7).name == rook){
                board.castling_right_Black = 1;
            }else{
                board.castling_right_Black = 0;
            }
        }else{
            board.castling_left_Black = 0;
            board.castling_right_Black = 0;
        }

        if(abs(change_x - x == 1) && board.GetValue(change_y,change_x).name == kletka && board.GetValue(y,x).name == pawns){
            if(board.GetValue(y,x).value_color != board.GetValue(change_y - 1,change_x).value_color){
                board.SetValue_kletka(board.last_move_change_y,board.last_move_change_x, kletka);
            }
            if(board.GetValue(y,x).value_color != board.GetValue(change_y + 1,change_x).value_color){
                board.SetValue_kletka(board.last_move_change_y,board.last_move_change_x, kletka);
            }
        }

        board.SetValue(change_y,change_x,y,x);
        board.SetValue_kletka(y,x, kletka);

        board.last_move_y = y;
        board.last_move_x = x;
        board.last_move_change_y = change_y;
        board.last_move_change_x = change_x;
       

       if(board.GetValue(change_y,change_x).name == king && board.GetValue(change_y,change_x).value_color == white){
            if(board.castling_left_White && change_x == 2){
                board.SetValue(7,3,7,0);
                board.SetValue_kletka(7,0, kletka);
            }
            if(board.castling_right_White && change_x == 6){
                board.SetValue(7,5,7,7);
                board.SetValue_kletka(7,7,kletka);
            }
       }
        if(board.GetValue(change_y,change_x).name == king && board.GetValue(change_y,change_x).value_color == black){
            if(board.castling_left_Black && change_x == 2){
                board.SetValue(0,3,0,0);
                board.SetValue_kletka(0,0, kletka);
            }
            if(board.castling_right_Black && change_x == 6){

                board.SetValue(0,5,0,7);
                board.SetValue_kletka(0,7, kletka);
            }
        }
    }

    int GetValueY() {return y;}

    int GetValueX() {return x;}

    int GetValue_c_Y() {return change_y;}

    int GetValue_c_X() {return change_x;}

    void SetValueX(int m_x) {x = m_x;}

    void SetValueY(int m_y) {y = m_y;}

    void SetValue_c_X(int m_cx) {change_x = m_cx;}

    void SetValue_c_Y(int m_cy) {change_y = m_cy;}
};



std :: vector<Move> move_king(int y, int x,Board board){
    int array_x [8] = {x + 1, x - 1, x, x, x + 1, x - 1, x + 1, x - 1};
    int array_y [8] = {y, y, y + 1, y - 1, y + 1, y + 1, y - 1, y - 1};

    std :: vector <Move> m_king;
    for(int i = 0; i < 8; i++){
        if((array_x[i] >= 0  && array_y[i] >= 0) && (array_y[i] < 8 && array_x[i] < 8)){
            if(board.GetValue(array_y[i],array_x[i]).name == kletka){
                m_king.push_back(Move(y,x,array_y[i],array_x[i]));
            }else if(board.GetValue(y,x).value_color != board.GetValue(array_y[i],array_x[i]).value_color){
                m_king.push_back(Move(y,x,array_y[i],array_x[i]));
            }
        }
    }
    
    return m_king;
}

std :: vector<Move> move_pawns_white(int y, int x,Board board){

    std :: vector <Move> m_pawns;

    if(y == 6){
        if(board.GetValue(y - 1,x).name == kletka){
            m_pawns.push_back(Move(y, x, y - 1, x));
            if(board.GetValue(y - 2,x).name == kletka){
                m_pawns.push_back(Move(y, x, y - 2, x));
            }
        }
    }else{
        if(y - 1 >= 0 && y - 1 < 8){
            if(board.GetValue(y - 1,x).name == kletka){
                m_pawns.push_back(Move(y, x, y - 1, x));
            }
        }
    }
    if(y - 1 >= 0 && x - 1 >= 0 && y - 1 < 8 && x - 1 < 8){
        if(board.GetValue(y - 1, x - 1).name != kletka && board.GetValue(y - 1, x - 1).value_color != board.GetValue(y, x).value_color){
            m_pawns.push_back(Move(y, x, y - 1, x - 1));
        }
    }
    if(y - 1 >= 0 && x + 1 >= 0 && y - 1 < 8 && x + 1 < 8){
        if(board.GetValue(y - 1, x + 1).name != kletka && board.GetValue(y - 1, x + 1).value_color != board.GetValue(y, x).value_color){
            m_pawns.push_back(Move(y, x, y - 1, x + 1)); 
        }
    }
    
    return m_pawns;
}

std :: vector<Move> move_pawns_black(int y, int x,Board board){
    std :: vector <Move> m_pawns;
    if(y == 1){
        if(board.GetValue(y + 1,x).name == kletka){
            m_pawns.push_back(Move(y, x, y + 1, x));
            if(board.GetValue(y + 2,x).name == kletka){
                m_pawns.push_back(Move(y, x, y + 2, x));
            }
        }
    }else{
        if(y + 1 >= 0 && y + 1 < 8){
            if(board.GetValue(y + 1,x).name == kletka){
                m_pawns.push_back(Move(y, x, y + 1, x));
            }
        }
    }
    if(y + 1 >= 0 && x - 1 >= 0 && y + 1 < 8 && x - 1 < 8){
        if(board.GetValue(y + 1, x - 1).name != kletka && board.GetValue(y + 1, x - 1).value_color != board.GetValue(y, x).value_color){
            m_pawns.push_back(Move(y, x, y + 1, x - 1));
        }
    }
        
    if(y + 1 >= 0 && x + 1 >= 0 && y + 1 < 8 && x + 1 < 8){
        if(board.GetValue(y + 1, x + 1).name != kletka && board.GetValue(y + 1, x + 1).value_color != board.GetValue(y, x).value_color){
            m_pawns.push_back(Move(y, x, y + 1, x + 1));
        }
    }
    
    return m_pawns;
}


std::vector<Move> move_knight(int y,int x,Board board){
    std :: vector <Move> m_knight;
    int array_x[8] = {x + 2, x + 2, x - 2, x - 2, x - 1, x + 1, x - 1, x + 1};
    int array_y[8] = {y - 1, y + 1, y - 1, y + 1, y - 2, y - 2, y + 2, y + 2};

    for(int i = 0; i < 8; i++){
        if((array_x[i] >= 0  && array_y[i] >= 0) && (array_y[i] < 8 && array_x[i] < 8)){
            if(board.GetValue(array_y[i],array_x[i]).name == kletka){
                m_knight.push_back(Move(y,x,array_y[i],array_x[i]));
            }
            if(board.GetValue(array_y[i],array_x[i]).name != kletka){
                if(board.GetValue(y,x).value_color != board.GetValue(array_y[i],array_x[i]).value_color){
                    m_knight.push_back(Move(y,x,array_y[i],array_x[i]));
                }
            }
        }
    }
    return m_knight;
}

std :: vector <Move> move_rook(int y,int x,Board board){
    std::vector <Move> m_rook;
    int array_x[28] = {};
    int array_y[28] = {};
    
    for (int i = 1, j = 8, k = 15,l = 22; i < 8; i++,j++,k++,l++){
        array_x[i - 1] = x + i;
        array_y[i - 1] = y;

        array_x[j - 1] = x - i;
        array_y[j - 1] = y;

        array_y[k - 1] = y + i;
        array_x[k - 1] = x;

        array_y[l - 1] = y - i;
        array_x[l - 1] = x;
    }
    for(int i = 0; i < 28; i = i + 7){
        for(int j = 0; j < 7; j++){
            if((array_x[i + j] >= 0  && array_y[i + j] >= 0) && (array_y[i + j] < 8 && array_x[i + j] < 8)){
                if(board.GetValue(array_y[i + j],array_x[i + j]).name == kletka){
                    m_rook.push_back(Move(y,x,array_y[i + j],array_x[i + j]));
                }
                if(board.GetValue(array_y[i + j],array_x[i + j]).name != kletka){
                    if(board.GetValue(y, x).value_color != board.GetValue(array_y[i + j],array_x[i + j]).value_color){
                        m_rook.push_back(Move(y,x,array_y[i + j],array_x[i + j]));
                    }
                    break;
                }
            }else{
                break;                
            }
        }
    }
    return m_rook;
}

std :: vector <Move> move_bishop(int y,int x,Board board){
    std::vector <Move> m_bishop;
    int array_x [28] = {};
    int array_y [28] = {};
    for (int i = 1, j = 8, k = 15,l = 22; i < 8; i++,j++,k++,l++){
        array_x[i - 1] = x + i;
        array_y[i - 1] = y + i;
        // x + 1 x + 2 ... x + 7 : y + 1 y + 2 ... y + 7
        array_x[j - 1] = x - i;
        array_y[j - 1] = y - i;
        // x - 1 x - 2 ... x - 7 : y - 1 y - 2 ... y - 7
        array_y[k - 1] = y + i;
        array_x[k - 1] = x - i;
        // x - 1 x - 2 ... x - 7 : y + 1 y + 2 ... y + 7
        array_y[l - 1] = y - i;
        array_x[l - 1] = x + i;
        // x + 1 x + 2 ... x + 7 : y - 1 y - 2 ... y - 7
    }
    for(int i = 0; i < 28; i = i + 7){
        for(int j = 0; j < 7; j++){
            if((array_x[i + j] >= 0  && array_y[i + j] >= 0) && (array_y[i + j] < 8 && array_x[i + j] < 8)){
                if(board.GetValue(array_y[i + j],array_x[i + j]).name == kletka){
                    m_bishop.push_back(Move(y,x,array_y[i + j],array_x[i + j]));
                }
                if(board.GetValue(array_y[i + j],array_x[i + j]).name != kletka){
                    if(board.GetValue(y, x).value_color != board.GetValue(array_y[i + j],array_x[i + j]).value_color){
                        m_bishop.push_back(Move(y,x,array_y[i + j],array_x[i + j]));
                    }
                    break;
                }
            }else{
                break;                
            }
        }
    }
    return m_bishop;
}



std :: vector <Move> move_queen(int y,int x,Board board){
    std :: vector <Move> m_queen1;
    std :: vector <Move> m_queen;
    m_queen1 = move_bishop(y,x,board);
    m_queen.insert(m_queen.end(),m_queen1.begin(),m_queen1.end());
    m_queen1 = move_rook(y,x,board);
    m_queen.insert(m_queen.end(),m_queen1.begin(),m_queen1.end());
    return m_queen;
}


std::string w_or_b(Figura pic){
    Figura_f chess_value[] = {pawns,knight,bishop,rook ,queen ,king,kletka};

    for (int i = 0; i < 6; i++){
        if(pic.name == chess_value[i]){
            if(pic.value_color == white){
                return whiteF[chess_value[i]];
            }
            else {
                return blackF[chess_value[i]];
            }
        }
    }
    return "_";
}

void danger_maps_king(int y,int x,int map_dang [rows][columns]){
    int array_x [8] = {x + 1, x - 1, x, x, x + 1, x - 1, x + 1, x - 1};
    int array_y [8] = {y, y, y + 1, y - 1, y + 1, y + 1, y - 1, y - 1};

    //Move.y
    for (int i = 0; i < 8; i++) {
	    if((array_x[i] >= 0  && array_y[i] >= 0) && (array_y[i] < 8 && array_x[i] < 8)){
	        map_dang[array_y[i]][array_x[i]] = 1;
	    }
    }

}


void danger_maps_pawns(int y, int x, int map_dang[rows][columns],Board board){
    if (board.GetValue(y, x).value_color == white){
        if(y - 1 >= 0 && x + 1 >= 0 && y - 1 < 8 && x + 1 < 8){
            map_dang[y - 1][x + 1] = 1;
        }
        if(y - 1 >= 0 && x - 1 >= 0 && y - 1 < 8 && x - 1 < 8){
            map_dang[y - 1][x - 1] = 1;
        }
    }else{
        if(y + 1 >= 0 && x + 1 >= 0 && y + 1 < 8 && x + 1 < 8){
            map_dang[y + 1][x + 1] = 1;
        }
        if(y + 1 >= 0 && x - 1 >= 0 && y + 1 < 8 && x - 1 < 8){
            map_dang[y + 1][x - 1] = 1;
        }      
    }


}

void danger_maps_rook(int y, int x, int map_dang[rows][columns],Board board){

    int array_x[28] = {};
    int array_y[28] = {};
    
    for (int i = 1, j = 8, k = 15,l = 22; i < 8; i++,j++,k++,l++){
        array_x[i - 1] = x + i;
        array_y[i - 1] = y;

        array_x[j - 1] = x - i;
        array_y[j - 1] = y;

        array_y[k - 1] = y + i;
        array_x[k - 1] = x;

        array_y[l - 1] = y - i;
        array_x[l - 1] = x;
    }

    for(int i = 0; i < 28; i = i + 7){
        for(int j = 0; j < 7; j++){
            if((array_x[i + j] >= 0  && array_y[i + j] >= 0) && (array_y[i + j] < 8 && array_x[i + j] < 8)){
                map_dang[array_y[i + j]][array_x[i + j]] = 1;
                if(board.GetValue(array_y[i + j],array_x[i + j]).name != kletka){
                    if(board.GetValue(y, x).value_color == board.GetValue(array_y[i + j],array_x[i + j]).value_color){
                        map_dang[array_y[i + j]][array_x[i + j]] = 0;
                    }
                    break;
                }
            }else{
                break;                
            }
        }
    }

}

void danger_maps_knight(int y, int x, int map_dang[rows][columns]){
    int array_x[8] = {x + 2, x + 2, x - 2, x - 2, x - 1, x + 1, x - 1, x + 1};
    int array_y[8] = {y - 1, y + 1, y - 1, y + 1, y - 2, y - 2, y + 2, y + 2};

    for (int i = 0; i < 8; i++) {
	    if((array_x[i] >= 0  && array_y[i] >= 0) && (array_y[i] < 8 && array_x[i] < 8)){
	        map_dang[array_y[i]][array_x[i]] = 1;
	    }
    }
}
//?
void danger_maps_bishop(int y, int x, int map_dang[rows][columns],Board board){
    int array_x [28] = {};
    int array_y [28] = {};

    for (int i = 1, j = 8, k = 15,l = 22; i < 8; i++,j++,k++,l++){
        array_x[i - 1] = x + i;
        array_y[i - 1] = y + i;
        // x + 1 x + 2 ... x + 7 : y + 1 y + 2 ... y + 7
        array_x[j - 1] = x - i;
        array_y[j - 1] = y - i;
        // x - 1 x - 2 ... x - 7 : y - 1 y - 2 ... y - 7
        array_y[k - 1] = y + i;
        array_x[k - 1] = x - i;
        // x - 1 x - 2 ... x - 7 : y + 1 y + 2 ... y + 7
        array_y[l - 1] = y - i;
        array_x[l - 1] = x + i;
        // x + 1 x + 2 ... x + 7 : y - 1 y - 2 ... y - 7
    }
    for(int i = 0; i < 28; i = i + 7){
        for(int j = 0; j < 7; j++){
            if((array_x[i + j] >= 0  && array_y[i + j] >= 0) && (array_y[i + j] < 8 && array_x[i + j] < 8)){
                map_dang[array_y[i + j]][array_x[i + j]] = 1;
                if(board.GetValue(array_y[i + j],array_x[i + j]).name != kletka){
                    if(board.GetValue(y, x).value_color == board.GetValue(array_y[i + j],array_x[i + j]).value_color){
                        map_dang[array_y[i + j]][array_x[i + j]] = 0;
                    }
                    break;
                }
            }else{
                break;                
            }
        }
    }
}

void danger_maps_queen(int y, int x, int map_dang[rows][columns],Board board){
    danger_maps_rook(y,x,map_dang,board);
    danger_maps_bishop(y,x,map_dang,board);
}


void field(Board board){
    std::string a = {"abcdefgh"};
    std::cout<< "  ";
    for (int j = 0; j < columns; j++) {
        std::cout << std::setw(2) << std::setiosflags(std::ios::left) << a[j];
    }
    for(int i = 0; i < rows; i++){
        std :: cout << "\n";
        for(int j = 0; j < columns; j++){
            if(j == 0){
                std :: cout << columns-i << "|";
            }
            if (board.GetValue(i, j).name == kletka){
                std :: cout << "_" << "|";
            }else {
                std::cout << w_or_b(board.GetValue(i, j)) << "|";
            }
            if(j == 7){
                std :: cout << columns-i;
            }
        }
    }    
    std :: cout << "\n";
    std::cout << "  ";
    for (int j = 0; j < columns; j++) {
        std::cout << std::setw(2) << std::setiosflags(std::ios::left) << a[j];
    }
    std :: cout << "\n";
}

void poss_move(std::vector<Move> figure,Board board){
    for(int i = 0; i < figure.size();i++){
        board.SetValue(figure[i].change_y,figure[i].change_x,figure[i].y,figure[i].x);
    }
    field(board);
    for(int i = 0; i < figure.size();i++){
        board.SetValue_kletka(figure[i].change_y,figure[i].change_x, kletka);
    }
}

std::vector<Move> castling(Board board,std::vector<Move> move_king){
    if(board.GetValue(7,4).value_color == white){    
        if(board.castling_left_White){
            if(board.GetValue(7,3).name == kletka && board.GetValue(7,2).name == kletka && board.GetValue(7,1).name == kletka){
                move_king.push_back(Move(7,4,7,2));
            }
        }
        if(board.castling_right_White){
            if(board.GetValue(7,5).name == kletka && board.GetValue(7,6).name == kletka){
                move_king.push_back(Move(7,4,7,6));
            } 
        }
    }else{
        if(board.castling_left_Black){
            if(board.GetValue(0,3).name == kletka && board.GetValue(0,2).name == kletka && board.GetValue(0,1).name == kletka){
                move_king.push_back(Move(0,4,0,2));
            }
            
        }
        if(board.castling_right_Black){
            if(board.GetValue(0,5).name == kletka && board.GetValue(0,6).name == kletka){
                move_king.push_back(Move(0,4,0,6)); 
            }
        }
    }

    return move_king;
}

std::vector<Move> en_passant_white(Board board,int y, int x){
    std::vector <Move> en_pass_pawns;
    if(abs(board.last_move_y - board.last_move_change_y) == 2 && board.GetValue(board.last_move_change_y,board.last_move_change_x).name == pawns){
        if(y == 3 && board.last_move_change_y == 3){
            if(y - 1 >= 0 && x - 1 >= 0 && y - 1 < 8 && x - 1 < 8){
                if(board.GetValue(y,x - 1).name == pawns){
                    en_pass_pawns.push_back(Move(y, x, y - 1, x - 1));
                }
            }
            if(y - 1 >= 0 && x + 1 >= 0 && y - 1 < 8 && x + 1 < 8){
                if(board.GetValue(y,x + 1).name == pawns){
                    en_pass_pawns.push_back(Move(y, x, y - 1, x + 1));
                }
            }
        }
    }
    return en_pass_pawns;
}

std::vector<Move> en_passant_black(Board board,int y, int x){
    std::vector <Move> en_pass_pawns;
    if(abs(board.last_move_y - board.last_move_change_y) == 2 && board.GetValue(board.last_move_change_y,board.last_move_change_x).name == pawns){
        if(y == 4 && board.last_move_change_y == 4){
            if(y + 1 >= 0 && x - 1 >= 0 && y + 1 < 8 && x - 1 < 8){
                if(board.GetValue(y,x - 1).name == pawns){
                    en_pass_pawns.push_back(Move(y, x, y + 1, x - 1));
                }
            }
            if(y + 1 >= 0 && x + 1 >= 0 && y + 1 < 8 && x + 1 < 8){
                if(board.GetValue(y,x + 1).name == pawns){
                    en_pass_pawns.push_back(Move(y, x, y + 1, x + 1));
                }
            }
        }
    }
    return en_pass_pawns;
}


std :: vector<Move> build_maps_move(Color value,Board board){
    std :: vector <Move> figure_move;
    for(int i = 0; i < columns; i++){
	    for(int j = 0; j < rows; j++){
            if(board.GetValue(i,j).value_color == value){
                if((board.GetValue(i,j).name == king)){
                    std :: vector <Move> figure_M_king = move_king(i,j,board);
                    figure_move.insert(figure_move.end(),figure_M_king.begin(),figure_M_king.end());
                    std :: vector<Move> figure_castling_king = castling(board,figure_M_king);
                    figure_move.insert(figure_move.end(),figure_castling_king.begin(),figure_castling_king.end());
                }
                if((board.GetValue(i,j).name == rook)){
                    std :: vector <Move> figure_M_rook = move_rook(i,j,board);
                    figure_move.insert(figure_move.end(),figure_M_rook.begin(),figure_M_rook.end());
                }
                if((board.GetValue(i,j).name == knight)){
                    std :: vector <Move> figure_M_knight = move_knight(i,j,board);
                    figure_move.insert(figure_move.end(),figure_M_knight.begin(),figure_M_knight.end());
                }
                if((board.GetValue(i,j).name == bishop)){
                    std :: vector <Move> figure_M_bishop = move_bishop(i,j,board);
                    figure_move.insert(figure_move.end(),figure_M_bishop.begin(),figure_M_bishop.end());
                }
                if((board.GetValue(i,j).name == queen)){
                    std :: vector <Move> figure_M_queen = move_queen(i,j,board);
                    figure_move.insert(figure_move.end(),figure_M_queen.begin(),figure_M_queen.end());
                }
                if((board.GetValue(i,j).name == pawns)){
                    if(value == white){
                        std :: vector <Move> figure_M_pawns = move_pawns_white(i,j,board);
                        figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
                        figure_M_pawns = en_passant_white(board,i,j);
                        figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
                    }
                    if(value == black){
                        std :: vector <Move> figure_M_pawns = move_pawns_black(i,j,board);
                        figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
                        figure_M_pawns = en_passant_black(board,i,j);
                        figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
                    }

                }
	        }
        }
    }
    return figure_move;
}

void build_maps_dan(int map_danger [rows][columns],Color value,Board board){
    for(int i = 0; i < rows; i++){
	    for(int j = 0; j < columns; j++){
            if((board.GetValue(i, j).value_color == value)){
                if((board.GetValue(i, j).name == king)){
                danger_maps_king(i,j,map_danger);
                }
                if((board.GetValue(i, j).name == rook)){
                    danger_maps_rook(i,j,map_danger,board);
                }
                if((board.GetValue(i, j).name == knight)){
                    danger_maps_knight(i,j,map_danger);
                }
                if((board.GetValue(i, j).name == bishop)){
                    danger_maps_bishop(i,j,map_danger,board);
                }
                if((board.GetValue(i, j).name == queen)){
                    danger_maps_queen(i,j,map_danger,board);
                }
                if((board.GetValue(i, j).name == pawns)){
                    danger_maps_pawns(i,j,map_danger,board);
                }
            }

	    }
    }

}

void field_map_dan(int attention1[columns][rows]){
    for(int i = 0; i < columns; i++){
	    std :: cout << "\n";
	    for(int j = 0; j < rows; j++){
	        std :: cout << attention1[i][j] << " ";
	    }
    }
    std::cout << "\n";  
}

void zero(int map_dang[columns][rows]){
    for(int i = 0; i < columns; i++){
	    for(int j = 0; j < rows; j++){
	        map_dang[i][j] = 0;
	    }
    }
}

int king_in_dangers(Color value_color,int y,int x,Board board){
    build_maps_dan(attention,value_color,board);
    if(attention[y][x]){
        zero(attention);
        return 1;
    }else{
        zero(attention);
        return 0;
    }

    

}

int finding_the_king(Color value_c,Board board){
    for(int i = 0; i < columns; i++){
        for(int j = 0; j < rows; j++){
            if (board.GetValue(i, j).name == king && board.GetValue(i, j).value_color == value_c){
                if(value_c == white){
                    return king_in_dangers(black,i,j,board);
                }else{
                    return king_in_dangers(white,i,j,board);
                }
            } 
        }
    }
    return 0;

}
Board copy(Board board){
    for(int i = 0;i < columns; i++){
        for(int j = 0; j < rows; j++){
            empty_board[i][j].name = board.GetValue(i, j).name;
            empty_board[i][j].value_color = board.GetValue(i, j).value_color;
        }
    }
    Board pos_move(empty_board);
    return pos_move;
}


std::vector<Move> king_danger(std::vector<Move> figure_move, Board board){
    std::vector<Move>figure_move_not_king_d;
    for(int i = 0; i < figure_move.size(); i++){
        Board copy_board = copy(board);
        figure_move[i].move_figura(copy_board);
        int danger_king = finding_the_king(copy_board.GetValue(figure_move[i].change_y,figure_move[i].change_x).value_color,copy_board);
        if(!danger_king){  
            figure_move_not_king_d.push_back(Move(figure_move[i].y,figure_move[i].x,figure_move[i].change_y,figure_move[i].change_x));
            
        }
        field(copy_board);
    }
    return figure_move_not_king_d;
}

Color change_move(Color sym){
    if (sym == white){
        return black;
    }else{
        return white;
    }
}

int conversion_x(std::string input){
    std :: string symbol = {"abcdefgh"};
    for(int i = 0; i < 8; i++){
        if(input[0] == symbol[i]){
            return i;
        }
    }
    throw std::invalid_argument("Неверный индекс или символ не является буквой");
}

int conversion_y(std::string input){
    
    char indexSym = input[1];
    int y = indexSym - '0';
    y = 8 - y;
    if (y > 8 || y < 0){
        throw std::invalid_argument("Неверный индекс или символ не является буквой");
    }else{
        return y;
    }
}

std::vector <Move> karta(Board board, int y, int x){
    std :: vector <Move>figure_move;
    if (board.GetValue(y,x).name == pawns){
        if(board.GetValue(y,x).value_color == white){
            std :: vector <Move> figure_M_pawns = move_pawns_white(y,x,board);
            figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
            figure_M_pawns = en_passant_white(board,y,x);
            figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
        }
        if(board.GetValue(y,x).value_color == black){
            std :: vector <Move> figure_M_pawns = move_pawns_black(y,x,board);
            figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
            figure_M_pawns = en_passant_black(board,y,x);
            figure_move.insert(figure_move.end(),figure_M_pawns.begin(),figure_M_pawns.end());
        }
    }
    if (board.GetValue(y,x).name == knight){
        figure_move = move_knight(y,x,board);
    }
    if (board.GetValue(y,x).name == bishop){
        figure_move = move_bishop(y,x,board);
    }
    if (board.GetValue(y,x).name == rook){
        figure_move = move_rook(y,x,board);
    }
    if (board.GetValue(y,x).name == queen){
        figure_move = move_queen(y,x,board);
    }
    if (board.GetValue(y,x).name == king){
        std :: vector <Move> figure_M_king = move_king(y,x,board);
        figure_move.insert(figure_move.end(),figure_M_king.begin(),figure_M_king.end());
        std :: vector<Move> figure_castling_king = castling(board,figure_M_king);
        figure_move.insert(figure_move.end(),figure_castling_king.begin(),figure_castling_king.end());
    }

    return figure_move;
}

int check_value_input(Board board,int y, int x, std::vector <Move> possible_move,Color sym){
    if(board.GetValue(y,x).name == kletka){
        std::cout << "no figure"<< std::endl;
        return 0;
    }
    if(board.GetValue(y,x).value_color != sym){
        std::cout << "Выберите заново фигуру нужного цвета"<< std::endl;
        return 0;
    }
    // possible_move = karta(board,y,x);
    if(!possible_move.size()){
        std::cout << "У фигуры нет ходов"<< std::endl;
        return 0;
    }
    return 1;
}

int check_value_castling_long(Color sym,Board board, int y, int x){
    if(sym == white){
        if(board.castling_left_White){
            if(board.GetValue(7,3).name == kletka && board.GetValue(7,2).name == kletka && board.GetValue(7,1).name == kletka){
                Move move_king(7,4,7,2);
                move_king.move_figura(board);
                std::cout << "Произведена рокировка"<< std::endl;
                field(board);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        if(board.castling_left_Black){
            if(board.GetValue(0,3).name == kletka && board.GetValue(0,2).name == kletka && board.GetValue(0,1).name == kletka){
                Move move_king(0,4,0,2);
                move_king.move_figura(board);
                std::cout << "Произведена рокировка"<< std::endl;
                field(board);
                return 1;
            }else{
                return 0;
            }

        }else{
            return 0;
        }
    }
}

int check_value_castling_short(Color sym,Board& board){
    if(sym == white){
        if(board.castling_right_White){
            if(board.GetValue(7,5).name == kletka && board.GetValue(7,6).name == kletka){
                Move move_king_cast(7,4,7,6);
                move_king_cast.move_figura(board);
                std::cout << "Произведена рокировка"<< std::endl;
                field(board);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        if(board.castling_right_Black){
            if(board.GetValue(0,5).name == kletka && board.GetValue(0,6).name == kletka){
                Move move_king_cast(0,4,0,6);
                move_king_cast.move_figura(board);
                std::cout << "Произведена рокировка"<< std::endl;
                field(board);
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }
}


void play_game(Board board){
    std::string input = {};
    int y,x;
    int change_y,change_x;
    Color sym = white;
    std::vector <Move> possible_move;
    
    for(int play = 0;play < 1;){
        field(board);
        for(int i = 0; ; ){
            std::cout << "Выберите фигуру: " << ((sym == white) ? "Ход белых" : "Ход черных") << std::endl;
            std :: cin >> input;
            if(input == "exit"){
                break;
            }
            if(input == "0-0-0"){
                if(check_value_castling_long(sym,board,y,x)){
                    sym = change_move(sym);
                    continue;
                }else{
                    std::cout << "Рокировка невозможна"<< std::endl;
                    continue;
                }
            }
            if(input == "0-0"){
                if(check_value_castling_short(sym,board)){
                    sym = change_move(sym);
                    continue;
                }else{
                    std::cout << "Рокировка невозможна"<< std::endl;
                    continue;
                }
            }
            x = conversion_x(input);
            y = conversion_y(input);
            possible_move = karta(board,y,x);
            if(check_value_input(board,y,x,possible_move,sym)){
                break;
            }else{
                continue;
            }
        }
        
        if(input == "exit"){
            break;
        }
        poss_move(possible_move,board);

        for(int i = 0; i < 1;){
            std::cout << "Сделайте ход" << std::endl;
            std :: cin >> input;
            if(input == "back"){
                break;
            }
            change_x = conversion_x(input);
            change_y = conversion_y(input);
            for(int j = 0; j < possible_move.size(); j++){
                if(possible_move[j].change_y == change_y && possible_move[j].change_x == change_x){
                    possible_move[j].move_figura(board);
                    i = 1;
                    break;
                }
            }
            if(!i){
                std:: cout << "Выбран неверный ход"<< std::endl;
                continue;
            }
        }
        if(input != "back"){
            sym = change_move(sym);
        }
    }
}

int main(){

    Board board(chess_board);

    play_game(board);

    return 0;
}