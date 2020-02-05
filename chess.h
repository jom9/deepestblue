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
		list <tuple <int,int>> attacks;// squares attacked by piece
		bool generic;
		bool enpass = false;
		bool firstmove = true;

		Piece();
		Piece(char c,int f,int r);
		bool inside(int x, int y);// is the piece inside the board

		virtual void updateLegalMoves(Square board[8][8]);
		// possible moves, empty for parent class, tuples
		virtual void updateAttacks(Square board[8][8]);
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
		void updateAttacks(Square board[8][8]);
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
		 list <tuple<int,int>> whitePos; //location of all white pieces
		 list <tuple<int,int>> blackPos;// location of all black pieces
		 //list <int,int> whitePiecesPos;
		 //list <int,int> blackPiecesPos;

			Board();

			bool isLegal(int xs,int ys,int xd,int yd); // checks if move is legal
			void updateBlack(int xs,int ys,int xd,int yd);// makes a move for black, assumed to be legal
			void updateWhite(int xs,int ys,int xd,int yd);// makes move for white, assumed to be legal
			tuple<int,int> captures(int xs,int ys,int xd,int yd);// returns 'w' if white captures black, return 'b' if black captures white, 'X' otherwise
			list <tuple<int,int,int,int>> legalMoves(); // all legal moves in current states
			void printBoard(); //test function for debugging
			bool takeMove(int xs,int ys,int xd,int yd);// takes a move, returns true if checkmate is on board.
			bool checkmate();// checks if checkmate is on board
      bool updateBoard();

};
