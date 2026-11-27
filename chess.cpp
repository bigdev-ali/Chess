#include<iostream>
#include<cstdlib>
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
bool PathClear(Move m){
    int steprow=0;
    int stepcol=0;
    if(m.ToRow>m.fromRow){
        steprow=1; //if the destination row is greater than the source row we need to step down
    }
    else if(m.ToRow<m.fromRow){ //if the destination row is less than the source row we need to step up
        steprow=-1;
    }
    if(m.ToCol>m.fromCol){ //same for col equal cases are handled at intialisation
        stepcol=1;
    }
    else if(m.ToCol<m.fromCol){
        stepcol=-1;
    }
    int r=m.fromRow+steprow;
    int c=m.fromCol+stepcol;
    while(r!=m.ToRow || c!=m.ToCol){
        if(board[r][c].piece==Piece::Empty){
           r=r+steprow;
           c=c+stepcol; 
        }
        else{
            return false;
        }
    }
    return true;
}
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
bool IsMoveValid(Move m){
    bool check=Boundary(m.ToRow,m.ToCol);
    bool valid=Boundary(m.fromRow,m.fromCol);
    if(check==false || valid==false){
        cout<<"Invalid move combination"<<endl;
        return false;
    }
    if(board[m.fromRow][m.fromCol].piece==Piece::Empty){
        cout<<"There is no piece in this position"<<endl;
        return false;
    }
     if(m.fromRow==m.ToRow && m.fromCol==m.ToCol){
        cout<<"This move does nothing"<<endl;
        return false;
    }
    if(board[m.fromRow][m.fromCol].color==board[m.ToRow][m.ToCol].color){
        cout<<"You can't capture a piece with the same color"<<endl;
       return false;
    }
        switch(board[m.fromRow][m.fromCol].piece){
            case Piece::Pawn:{
                int dr=m.ToRow-m.fromRow;
                int dc=abs(m.ToCol-m.fromCol);
                if(dc==0){
                    if(board[m.fromRow][m.fromCol].color==Color::White && dr==-1 && board[m.ToRow][m.ToCol].piece==Piece::Empty){
                        return true;
                    }
                    if((board[m.fromRow][m.fromCol].color==Color::Black && dr==1 && board[m.ToRow][m.ToCol].piece==Piece::Empty)){
                        return true;
                    }
                    if((board[m.fromRow][m.fromCol].color==Color::Black && m.fromRow==1 && dr==2 && board[m.ToRow][m.ToCol].piece==Piece::Empty && PathClear(m)==true)){
                        return true;
                    }
                    if((board[m.fromRow][m.fromCol].color==Color::White && m.fromRow==6 && dr==-2 && board[m.ToRow][m.ToCol].piece==Piece::Empty && PathClear(m)==true)){
                        return true;
                    }
                    }
                if(dc==1){
                    if(board[m.fromRow][m.fromCol].color==Color::White && dr==-1 && board[m.ToRow][m.ToCol].color==Color::Black){
                        return true;
                    }
                    if(board[m.fromRow][m.fromCol].color==Color::Black && dr==1 && board[m.ToRow][m.ToCol].color==Color::White){
                        return true;
                    }
                }
            return false;
            }
            case Piece::Knight:{
            int dr=abs(m.ToRow-m.fromRow);
            int dc=abs(m.ToCol-m.fromCol);
            if((dr==1 && dc==2) || (dr==2 && dc==1)){
                return true;
            }
            else{
                return false;
            }
        }
            case Piece::Bishop:{
                int dr=abs(m.ToRow-m.fromRow);
                int dc=abs(m.ToCol-m.fromCol);
                if((dc==dr) && (PathClear(m)==true)){
                    return true;
                }
                else{
                    return false;
                }
            }
            case Piece::Queen:{
                int dr=abs(m.ToRow-m.fromRow);
                int dc=abs(m.ToCol-m.fromCol);
                if((dc==dr || m.ToCol==m.fromCol || m.ToRow==m.fromRow) && (PathClear(m)==true)){
                    return true;
                }
                else{
                    return false;
                }
            }
            case Piece::Rook:
            if((m.ToCol==m.fromCol||m.ToRow==m.fromRow) && (PathClear(m)==true)){
                return true;
            }
            else{
            return false;
            }
            case Piece::King:{
                int dr=abs(m.ToRow-m.fromRow);
                int dc=abs(m.ToCol-m.fromCol);
                if(dr<=1 && dc<=1){
                    return true;
                }
                else{
                    return false;
                }
            }
            default:
            return false;
        }
}
void Test(Move m, const char* label){
    cout << label << ": " << (IsMoveValid(m) ? "valid" : "invalid") << endl;
}
int main(){
    Setupboard();

    // fromRow, fromCol, ToRow, ToCol
    Test({6,4,5,4}, "White pawn one step (expect valid)");
    Test({6,4,4,4}, "White pawn two steps (expect valid)");
    Test({6,4,3,4}, "White pawn three steps (expect invalid)");
    Test({6,4,5,5}, "White pawn diagonal onto empty square (expect invalid)");
    Test({1,3,3,3}, "Black pawn two steps (expect valid)");

    // black knight in front of the e-pawn, black knight behind it diagonally,
    // white knight in front of the black d-pawn, white a-pawn off its start row
    MakeMove({0,1,5,4});
    MakeMove({0,6,7,5});
    MakeMove({7,1,2,3});
    MakeMove({6,0,4,0});
    PrintBoard();

    Test({6,4,5,4}, "White pawn blocked one step (expect invalid)");
    Test({6,4,4,4}, "White pawn double step blocked in the middle (expect invalid)");
    Test({6,3,5,4}, "White pawn captures diagonally forward (expect valid)");
    Test({6,4,7,5}, "White pawn captures backward (expect invalid)");
    Test({1,4,2,3}, "Black pawn captures diagonally forward (expect valid)");
    Test({1,3,2,3}, "Black pawn blocked one step (expect invalid)");
    Test({1,3,3,3}, "Black pawn double step blocked in the middle (expect invalid)");
    Test({4,0,2,0}, "Pawn double step off its start row (expect invalid)");

    return 0;
}