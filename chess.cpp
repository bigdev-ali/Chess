#include<iostream>
using namespace std;
enum class Piece{King,Queen,Knight,Rook,Pawn,Bishop,Empty};
enum class Color{White,Black,None};
struct Square{
    Piece piece;
    Color color;
};
Square board[8][8];
void CleanBoard(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            board[i][j].piece=Piece::Empty;
            board[i][j].color=Color::None;
        }
    }
}
void Setupboard(){
    CleanBoard();
    for(int i=0;i<8;i++){
        board[1][i].piece=Piece::Pawn;
        board[1][i].color=Color::Black;
        board[6][i].piece=Piece::Pawn;
        board[6][i].color=Color::White;
        if(i==0||i==7){
            board[0][i].piece=Piece::Rook;
            board[0][i].color=Color::Black;
            board[7][i].piece=Piece::Rook;
            board[7][i].color=Color::White;
        }
        if(i==1||i==6){
            board[0][i].piece=Piece::Knight;
            board[0][i].color=Color::Black;
            board[7][i].piece=Piece::Knight;
            board[7][i].color=Color::White;
        }
        if(i==2||i==5){
            board[0][i].piece=Piece::Bishop;
            board[0][i].color=Color::Black;
            board[7][i].piece=Piece::Bishop;
            board[7][i].color=Color::White;
        }
        if(i==3){
            board[0][i].piece=Piece::Queen;
            board[0][i].color=Color::Black;
            board[7][i].piece=Piece::Queen;
            board[7][i].color=Color::White;
        }
        if(i==4){
            board[0][i].piece=Piece::King;
            board[0][i].color=Color::Black;
            board[7][i].piece=Piece::King;
            board[7][i].color=Color::White;
        }
    }
}
char SquaretoChar(Square s){
    if(s.piece==Piece::Empty){
        return '.';
    }
    else if(s.piece==Piece::Pawn){
        return (s.color==Color::White)?'P':'p';  //if color is white return P else return p
    }
    else if(s.piece==Piece::Rook){
        return (s.color==Color::White)?'R':'r';
    }
    else if(s.piece==Piece::Knight){
        return (s.color==Color::White)?'N':'n';
    }
    else if(s.piece==Piece::Bishop){
        return (s.color==Color::White)?'B':'b';
    }
    else if(s.piece==Piece::Queen){
        return (s.color==Color::White)?'Q':'q';
    }
    else if(s.piece==Piece::King){
        return (s.color==Color::White)?'K':'k';
    }
    else{
        return '?'; //to catch if something is broken
    }
}
void PrintBoard(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            cout<<SquaretoChar(board[i][j])<<" ";
        }
        cout<<endl;
    }
}
struct Move{
    int fromRow;
    int fromCol;
    int ToRow;
    int ToCol;
};
bool Boundary(int row,int col){
   return row >= 0 && row <= 7 && col >= 0 && col <= 7;
}
void MakeMove(Move m){
    bool check=Boundary(m.ToRow,m.ToCol);
    bool valid=Boundary(m.fromRow,m.fromCol);
    if(check==false || valid==false){
        cout<<"Invalid move combination"<<endl;
    }
    if(check==true && valid==true){
        board[m.ToRow][m.ToCol]=board[m.fromRow][m.fromCol];
        board[m.fromRow][m.fromCol].piece=Piece::Empty;
        board[m.fromRow][m.fromCol].color=Color::None;
    }
}
int main(){
    Setupboard();
    Move pawnm={6,1,5,1};
    MakeMove(pawnm);
    PrintBoard();
    return 0;
}
