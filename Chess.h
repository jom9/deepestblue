// Board is set up as follows: bottom corner is (0,0) and top right corner (7,7)
#include "BitBoard.h"
#include<stdio.h>

class Chess{
  private:
    BitBoard board;

    BitBoard WhitePawns;
    BitBoard BlackPawns;

    BitBoard WhiteKnights;
    BitBoard BlackKnights;

    BitBoard WhiteBishops;
    BitBoard BlackBishops;

    BitBoard WhiteRooks;


    BitBoard WhiteQueen;
    BitBoard BlackQueen;

    BitBoard WhiteKing;
    BitBoard BlackKing;

    BitBoard WhitePieces;
    BitBoard BlackPieces;

    BitBoard WhiteAttacks;
    BitBoard BlackAttacks;

    BitBoard UnMovedBlackPawns;
    BitBoard UnMovedWhitePawns;
  public:
    BitBoard BlackRooks;
    bool promote;
    char player;
    void Update();
    void StartGame();
    void PrintBoard();// prints current board, for debugging
    bool IsLegal(int x,int y);// return true if a the move is legal

    BitBoard BlackPawnMoves(int x,int y);
    BitBoard WhitePawnMoves(int x,int y);
    BitBoard BlackKnightMoves(int x, int y);
    BitBoard WhiteKnightMoves(int x, int y);
    BitBoard BlackBishopMoves(int x, int y);
    BitBoard WhiteBishopMoves(int x, int y);
    BitBoard BlackRookMoves(int x, int y);
    BitBoard WhiteRookMoves(int x, int y);
    BitBoard BlackQueenMoves(int x,int y);
    BitBoard WhiteQueenMoves(int x,int y);
    BitBoard BlackKingMoves(int x,int y);
    BitBoard WhiteKingMoves(int x,int y);
    void Promote(int xs,int ys, int xd, int yd);
    void RemovePiece(int x, int y, char c);
    void Move(int xs,int ys,int xd, int yd); //make a move


};
