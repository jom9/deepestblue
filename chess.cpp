#include <iostream>
#include <list>
#include <tuple>


using namespace std;



class Piece{
	public:
		int file,rank;
		char color;
		char rep; // character represntation
		list <tuple <int,int>> legalMoves;
		list <tuple <int,int>> checkingMoves;
		bool generic = true;

		Piece(){rep = 'X';}
		Piece(char c,int f,int r){
			file = f;
			rank = r;
			color =c;

		}
		bool inside(int x, int y){// is the piece inside the board

			if(x>7 || x<0){ return false;}
			if(y>7 || y<0){ return false;}
			return true;
		}
		virtual void updateLegalMove(){
		// possible moves, empty for parent class, tuples
		}
};

class King:public Piece{
	public:

		King(char c,int x,int y):Piece(c,x,y){rep = 'K'; generic = false;	}



};
class Knight:public Piece{
	public:

		Knight(char c,int x,int y):Piece(c,x,y){rep = 'N'; generic = false;	}

};
class Pawn:public Piece{
	public:

		Pawn(char c,int x,int y):Piece(c,x,y){rep ='P'; generic = false;	}

};
class Rook:public Piece{
	public:

		Rook(char c,int x,int y):Piece(c,x,y){rep ='R';	 generic = false;}

};
class Bishop:public Piece{
	public:

		Bishop(char c,int x,int y):Piece(c,x,y){rep ='B';	 generic = false;}

};
class Queen:public Piece{
	public:

		Queen(char c,int x,int y):Piece(c,x,y){rep ='Q'; generic = false;	}

};



class Square{
public:
	Piece piece;
	int file,rank;
	int attackedBy = 0; // number of pieces attaking this square
	char color;
	Square(){		}
	Square(int f,int r){
		file = f;
		rank = r;
	}
	void setPos(int f,int r){ // sets position of square
		file = f;
		rank = r;
	}
	tuple <int,int> getPos(){ // returns values of square
		return make_tuple(file,rank);
	}


};


class Board{

	public:
		char currentPlayer ='w';
		int turnNum=1;
		 Square board[8][8];
		Board(){
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					board[i][j].setPos(i,j); // inits board, sets square coors
					if(j%2 == 0){
						if(i%2 == 0){
							board[i][j].color = 'b';
						}
						else{
							board[i][j].color = 'w';
						}
					}
					else{
						if(i%2 == 0){
							board[i][j].color = 'w';
						}
						else{
							board[i][j].color = 'b';
						}
					}
				}

			}

			for(int i=0;i<8;i++){
				board[i][1].piece = Pawn('w',i,1);// sets white pawns
				board[i][6].piece = Pawn('b',i,6);// sets black pawns
			}
			board[0][0].piece = Rook('w',0,0);// sets rooks
			board[7][0].piece = Rook('w',7,0);
			board[0][7].piece = Rook('b',0,7);
			board[7][7].piece = Rook('b',7,7);

			board[1][0].piece = Knight('w',1,0);// sets rooks
			board[6][0].piece = Knight('w',6,0);
			board[1][7].piece = Knight('b',1,7);
			board[6][7].piece = Knight('b',6,7);

			board[2][0].piece =  Bishop('w',2,0);// sets bishop
			board[5][0].piece = Bishop('w',5,0);
			board[2][7].piece = Bishop('b',2,7);
			board[5][7].piece = Bishop('b',5,7);

			board[3][0].piece =  Queen('w',3,0);// sets major piece
			board[4][0].piece = King('w',4,0);
			board[3][7].piece = Queen('b',3,7);
			board[4][7].piece = King('b',4,7);

			}
			void printBoard(){ //test function for debugging
				for(int j=7;j>=0;j--){
						for(int i=0;i<8;i++){
							if(board[i][j].piece.color == 'w'){
								cout<<"\033[0;31m" <<board[i][j].piece.rep<<"\033[0m" <<"\t";
							}
							else if (board[i][j].piece.color == 'b'){
								cout<<"\033[0;34m"<<board[i][j].piece.rep<<"\033[0m"<<"\t";
							}
							else{
								cout<<board[i][j].piece.rep<<"\t";
							}
							//std::cout << "\x1B[34m" << "Hello World!\n" << "\x1B[0m";
						}
						cout<<"\n";
				}
			}
			void takeMove(int xs,int ys,int xd,int yd){
				if(board[xs][ys].piece.rep == 'X'){
					cout<< "No piece here\n";
					return;
				}
				else if(currentPlayer == 'w'){
					if(board[xs][ys].piece.color == 'b'){
						cout<<"Not your piece";
					}
					else{
						Piece place =board[xd][yd].piece;
						board[xd][yd].piece =	board[xs][ys].piece ;
						board[xs][ys].piece =  place;
					}
				}
				else{
					if(board[xs][ys].piece.color == 'w'){
						cout<<"Not your piece";
					}
					else{
						Piece place =board[xd][yd].piece;
						board[xd][yd].piece =	board[xs][ys].piece ;
						board[xs][ys].piece =  place;
					}

				}
			}
};
int main(){

	Board b;
	b.printBoard();
	int xs,ys,xd,yd;
	while(true){
		cin>>xs>>ys>>xd>>yd;
		if(xs == -1 && ys == -1 && xd == -1 && yd == -1){
			cout<<"Done!";
			break;
		}
		else{
			b.takeMove(xs,ys,xd,yd);
		}
		b.printBoard();
	}


	return 0;
}
