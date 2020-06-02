// Board is set up as follows: bottom corner is (0,0) and top right corner (7,7)
#ifndef CHESS_H
#define CHESS_H
#include <exception>
#include "BitBoard.h"
#include<stdio.h>

class InvalidMove : public std::exception
{
public:
  virtual const char* what() const noexcept{ return "Invalid Move"; }
};
class Chess{
  private:

  public:
    BitBoard board;

    BitBoard WhitePawns;
    BitBoard BlackPawns;

    BitBoard WhiteKnights;
    BitBoard BlackKnights;

    BitBoard WhiteBishops;
    BitBoard BlackBishops;

    BitBoard WhiteRooks;
    BitBoard BlackRooks;

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


    bool promote=false;
    char player='w';
    void Update();// must update all bit boards!
    void StartGame();// same dependencieces as Update();
    Chess * Copy();
    bool IsLegal(int x,int y);// return true if a the move is legal
    void Promote(int xs,int ys, int xd, int yd);
    void RemovePiece(int x, int y, char c);
    void Move(int xs,int ys,int xd, int yd); //make a move, dependent on RemovePiece, Promote


    void PrintBoard();// prints current board, for php calls
    void PrintBoard(bool debug);// prints board, for debuging
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





};
#endif
