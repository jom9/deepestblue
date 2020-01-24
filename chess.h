#include <list>
#include <tuple>

using namespace std;
class Square;
class Piece{
	public:
		int file,rank;
		char color;
		char rep; // character represntation
		list <tuple <int,int>> legalMoves;
		bool generic;
		bool enpass = false;
		bool firstmove = true;
		Piece();
		Piece(char c,int f,int r);
		bool inside(int x, int y);// is the piece inside the board

		virtual void updateLegalMoves(Square board[8][8]);
		// possible moves, empty for parent class, tuples
    virtual void updatePos(int f,int r);
};
class Square{
public:
	Piece  piece;
	int file,rank;
	int attackedByWhite; // number of pieces attaking this square
	int attackedByBlack ;
	char color;
	Square();
	Square(int f,int r);
	void setPos(int f,int r); // sets position of square

	tuple <int,int> getPos();// returns values of square



};

class King:public Piece{
	public:

		King(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);



};
class Queen:public Piece{
	public:

		Queen(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);



};

class Knight:public Piece{
	public:

		Knight(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);
};
class Rook:public Piece{
	public:

		Rook(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);



};
class Bishop:public Piece{
	public:

		Bishop(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);

};
class Pawn:public Piece{
	public:
    bool firstmove = true;
		Pawn(char c,int x,int y);
		void updateLegalMoves(Square board[8][8]);



};

class Board{

	public:
		char currentPlayer ='w';
		int turnNum=1;
		 Square board[8][8];
		 bool wchecked = false;
		 bool bchecked = false;
		 tuple <int,int> wkingPos =  make_tuple(4,0);
		 tuple <int,int> bkingPos =  make_tuple(4,7);
		Board();

			void printBoard(); //test function for debugging
			void takeMove(int xs,int ys,int xd,int yd);
      void updateBoard();

};
