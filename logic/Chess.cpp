#include "Chess.h"
#include<stdio.h>
#include <iostream>
/*
  00 01 02 03 04 05 06 07
  08 09 10 11 12 13 14 15
  16 17 18 19 20 21 22 23
  24 25 26 27 28 29 30 31
  32 33 34 35 36 37 38 39
  40 41 42 43 44 45 46 47
  48 49 50 51 52 53 54 55
  56 57 58 59 60 61 62 63

  so each bit in the bitboard is a a square, ie
  00 = 0000000000000000000000000000000000000000000000000000000000000001
  01 = 0000000000000000000000000000000000000000000000000000000000000010
  11 = 0000000000000000000000000000000000000000000000000000000000000000
  63 = 1000000000000000000000000000000000000000000000000000000000000000
*/


void Chess::StartGame(){
  player = 'w';
  for(int i=0; i<8; i++){
    this->BlackPawns.SetOn(i,1);// Sets black pawns
    this->WhitePawns.SetOn(i,6);// Sets white pawns
  }

  this->UnMovedWhitePawns = this->WhitePawns;// keeps track of the unmoved pawns for enpassent
  this->UnMovedBlackPawns = this->BlackPawns;//



  this->BlackKnights.SetOn(1,0);// sets black knights
  this->BlackKnights.SetOn(6,0);
  this->WhiteKnights.SetOn(1,7);//sets white knights
  this->WhiteKnights.SetOn(6,7);

  this->BlackBishops.SetOn(2,0);// sets bishops
  this->BlackBishops.SetOn(5,0);
  this->WhiteBishops.SetOn(2,7);
  this->WhiteBishops.SetOn(5,7);

  this->BlackRooks.SetOn(0,0);// sets rooks
  this->BlackRooks.SetOn(7,0);
  this->WhiteRooks.SetOn(0,7);
  this->WhiteRooks.SetOn(7,7);

  this->BlackQueen.SetOn(3,0);// sets queen
  this->WhiteQueen.SetOn(3,7);

  this->BlackKing.SetOn(4,0);// sets king
  this->WhiteKing.SetOn(4,7);

  this->BlackPieces = this->BlackKing;  //this variable keeps track of all the white pieces, doesn't distinguash between type
  this->BlackPieces = BitBoard::Or(BlackPawns,this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackQueen, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackBishops, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackKnights, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackRooks,this->BlackPieces);

  this->WhitePieces = this->WhiteKing;// keeps track of location of all the pieces
  this->WhitePieces = BitBoard::Or(WhitePawns,this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteQueen, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteBishops, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteKnights, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteRooks,this->WhitePieces);

  this->promote = false;// bool that keeps track if something needs to be promoted

}
BitBoard Chess::BlackPawnMoves(int x,int y){// generates possible black pawn moves at pos x y
  BitBoard B;
  if(this->UnMovedBlackPawns.IsSet(x,y)){
    B.SetOn(x,y+2);// pawns can move 2 square in begining
  }
  if(BitBoard::Inside(x,y+1)){
    if(!this->WhitePieces.IsSet(x,y+1) && !this->BlackPieces.IsSet(x,y+1)){
      B.SetOn(x,y+1);// standard forward by 1
    }

  }
  if(BitBoard::Inside(x-1,y+1)){
    if(this->WhitePieces.IsSet(x-1,y+1) ){
      B.SetOn(x-1,y+1);//captures left
    }
    else if(this->UnMovedWhitePawns.IsSet(x-1,y+1)){
      B.SetOn(x-1,y+1);//captures enpassent
    }
  }
  if(BitBoard::Inside(x+1,y+1)){
    if(this->WhitePieces.IsSet(x+1,y+1) ){
      B.SetOn(x+1,y+1);// right
    }
    else if(this->UnMovedWhitePawns.IsSet(x+1,y+1)){
      B.SetOn(x+1,y+1);// captures enpassent
    }
  }
  return B;
}
BitBoard Chess::WhitePawnMoves(int x,int y){//generates white pawn moves at pos x y
  BitBoard B;
  if(this->UnMovedWhitePawns.IsSet(x,y)){
    B.SetOn(x,y-2);
  }
  if(BitBoard::Inside(x,y-1)){
    if(!this->WhitePieces.IsSet(x,y-1) && !this->BlackPieces.IsSet(x,y-1)){
      B.SetOn(x,y-1);
    }
  }
  if(BitBoard::Inside(x-1,y-1)){
    if(this->BlackPieces.IsSet(x-1,y-1) ){
      B.SetOn(x-1,y-1);
    }
    else if(this->UnMovedBlackPawns.IsSet(x-1,y-1)){
      B.SetOn(x-1,y-1);
    }
  }
  if(BitBoard::Inside(x+1,y-1)){
    if(this->BlackPieces.IsSet(x+1,y-1) ){
      B.SetOn(x+1,y-1);
    }
    else if(this->UnMovedBlackPawns.IsSet(x+1,y-1)){
      B.SetOn(x+1,y-1);
    }
  }


  return B;
}
BitBoard Chess::BlackKnightMoves(int x, int y){// get knights ,oves
   BitBoard B;
   for(int i = -2; i<3; i++){
     for(int j = -2; j<3; j++){
       if(i==0 || j==0){
         continue;
       }
       if(BitBoard::Inside(x+i,y+j) && !this->BlackPieces.IsSet(x+i,y+j)){
         B.SetOn(x+i,y+j);
       }
     }
   }
   return B;
}
BitBoard Chess::WhiteKnightMoves(int x, int y){
  BitBoard B;
  for(int i = -2; i<3; i++){
    for(int j = -2; j<3; j++){
      if(i==0 || j==0){
        continue;
      }
      if(BitBoard::Inside(x+i,y+j) && !this->WhitePieces.IsSet(x+i,y+j)){
        B.SetOn(x+i,y+j);
      }
    }
  }
  return B;
}
BitBoard Chess::BlackBishopMoves(int x, int y){
  BitBoard B;
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y+i) && !this->BlackPieces.IsSet(x+i,y+i) ){
    B.SetOn(x+i,y+i);
    if( this->WhitePieces.IsSet(x+i,y+i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y-i) && !this->BlackPieces.IsSet(x-i,y-i) ){
    B.SetOn(x-i,y-i);
    if( this->WhitePieces.IsSet(x-i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x+i,y-i) && !this->BlackPieces.IsSet(x+i,y-i) ){
    B.SetOn(x+i,y-i);
    if( this->WhitePieces.IsSet(x+i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y+i) && !this->BlackPieces.IsSet(x-i,y+i) ){
    B.SetOn(x-i,y+i);
    if( this->WhitePieces.IsSet(x-i,y+i) ){
      break;
    }
    i++;
  }
  return B;

}
BitBoard Chess::WhiteBishopMoves(int x, int y){
  BitBoard B;
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y+i) && !this->WhitePieces.IsSet(x+i,y+i) ){
    B.SetOn(x+i,y+i);
    if( this->BlackPieces.IsSet(x+i,y+i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y-i) && !this->WhitePieces.IsSet(x-i,y-i) ){
    B.SetOn(x-i,y-i);
    if( this->BlackPieces.IsSet(x-i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x+i,y-i) && !this->WhitePieces.IsSet(x+i,y-i) ){
    B.SetOn(x+i,y-i);
    if( this->BlackPieces.IsSet(x+i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y+i) && !this->WhitePieces.IsSet(x-i,y+i) ){
    B.SetOn(x-i,y+i);
    if( this->BlackPieces.IsSet(x-i,y+i) ){
      break;
    }
    i++;
  }
  return B;
}
BitBoard Chess::BlackRookMoves(int x, int y){
  BitBoard B;
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y) && !this->BlackPieces.IsSet(x+i,y) ){
    B.SetOn(x+i,y);
    if( this->WhitePieces.IsSet(x+i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y) && !this->BlackPieces.IsSet(x-i,y) ){
    B.SetOn(x-i,y);
    //std::cout<<x-i<<y<<'\n';
    if( this->WhitePieces.IsSet(x-i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y-i) && !this->BlackPieces.IsSet(x,y-i) ){
    B.SetOn(x,y-i);

    if( this->WhitePieces.IsSet(x,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y+i) && !this->BlackPieces.IsSet(x,y+i) ){
    B.SetOn(x,y+i);
    if( this->WhitePieces.IsSet(x,y+i) ){
      break;
    }
    i++;
  }
  return B;
}
BitBoard Chess::WhiteRookMoves(int x, int y){
  BitBoard B;
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y) && !this->WhitePieces.IsSet(x+i,y) ){
    B.SetOn(x+i,y);
    if( this->BlackPieces.IsSet(x+i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y) && !this->WhitePieces.IsSet(x-i,y) ){
    B.SetOn(x-i,y);
    if( this->BlackPieces.IsSet(x-i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y-i) && !this->WhitePieces.IsSet(x,y-i) ){
    B.SetOn(x,y-i);
    if( this->BlackPieces.IsSet(x,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y+i) && !this->WhitePieces.IsSet(x,y+i) ){
    B.SetOn(x,y+i);
    if( this->BlackPieces.IsSet(x,y+i) ){
      break;
    }
    i++;
  }
  return B;
}
BitBoard Chess::BlackQueenMoves(int x,int y){
  BitBoard B1,B2;
  B1 = BlackRookMoves(x,y);
  B2 = BlackBishopMoves(x,y);
  return BitBoard::Or(B1,B2);
}
BitBoard Chess::WhiteQueenMoves(int x,int y){
  BitBoard B1,B2;
  B1 = WhiteRookMoves(x,y);
  B2 = WhiteBishopMoves(x,y);
  return BitBoard::Or(B1,B2);
}
BitBoard Chess::BlackKingMoves(int x,int y){
  BitBoard B;
  for(int i=-1; i<2;i++){
    for(int j=-1; j<2;j++){
      if(i==0 || j== 0 || BitBoard::Inside(x+i,y+i) || this->BlackPieces.IsSet(x+i,y+i)){
        continue;
      }
      B.SetOn(x+i,y+i);
    }
  }
  return B;
}
BitBoard Chess::WhiteKingMoves(int x,int y){
  BitBoard B;
  for(int i=-1; i<2;i++){
    for(int j=-1; j<2;j++){
      if(i==0 || j== 0 || BitBoard::Inside(x+i,y+i) || this->WhitePieces.IsSet(x+i,y+i)){
        continue;
      }
      B.SetOn(x+i,y+i);
    }
  }
  return B;
}
void Chess::Update(){
  this->BlackPieces.SetAll(false);
  this->BlackPieces = BitBoard::Or(BlackPawns,this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackQueen, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackBishops, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackKnights, this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackRooks,this->BlackPieces);
  this->BlackPieces = BitBoard::Or(BlackKing,this->BlackPieces);

  this->WhitePieces.SetAll(false);
  this->WhitePieces = BitBoard::Or(WhitePawns,this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteQueen, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteBishops, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteKnights, this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteRooks,this->WhitePieces);
  this->WhitePieces = BitBoard::Or(WhiteKing,this->WhitePieces);


}

void Chess::RemovePiece(int x, int y, char c){

    if(c == 'b'){
      if(this->WhitePawns.IsSet(x,y)){ this->WhitePawns.SetOff(x,y); }
      if(this->WhiteBishops.IsSet(x,y)){ this->WhiteBishops.SetOff(x,y); }
      if(this->WhiteRooks.IsSet(x,y)){ this->WhiteRooks.SetOff(x,y); }
      if(this->WhiteKnights.IsSet(x,y)){ this->WhiteKnights.SetOff(x,y); }
      if(this->WhitePawns.IsSet(x,y)){ this->WhitePawns.SetOff(x,y); }
    }
    else if( c == 'w'){
      if(this->BlackPawns.IsSet(x,y)){ this->BlackPawns.SetOff(x,y); }
      if(this->BlackBishops.IsSet(x,y)){ this->BlackBishops.SetOff(x,y); }
      if(this->BlackRooks.IsSet(x,y)){ this->BlackRooks.SetOff(x,y); }
      if(this->BlackKnights.IsSet(x,y)){ this->BlackKnights.SetOff(x,y); }
      if(this->BlackPawns.IsSet(x,y)){ this->BlackPawns.SetOff(x,y); }
    }
}
void Chess::Promote(int xs ,int ys, int xd,int yd){
  std::cout<<"Promote"<<xs<<ys<<'\n';
  if(this->promote){
    if( player =='w'  && ys == 0){
      if(xd == -1 &&yd == -1){
        this->WhitePawns.SetOff(xs,ys);
        this->WhiteQueen.SetOn(xs,ys);
      }else if(xd =-2 && xd ==-2){
        this->WhitePawns.SetOff(xs,ys);
        this->WhiteRooks.SetOn(xs,ys);
      }
      else if(xd == -3 && yd == -3){
        this->WhitePawns.SetOff(xs,ys);
        this->WhiteBishops.SetOn(xs,ys);
      }
      else if(xd == -4 && yd == -4){
        this->WhitePawns.SetOff(xs,ys);
        this->WhiteKnights.SetOn(xs,xs);
      }
      this->player = 'b';
    }
    else if(ys == 7){
      if(xd == -1 &&yd == -1){
        this->BlackPawns.SetOff(xs,ys);
        this->BlackQueen.SetOn(xs,ys);
      }else if(xd =-2 && xd ==-2){
        this->BlackPawns.SetOff(xs,ys);
        this->BlackRooks.SetOn(xs,ys);
      }
      else if(xd == -3 && yd == -3){
        this->BlackPawns.SetOff(xs,ys);
        this->BlackBishops.SetOn(xs,ys);
      }
      else if(xd == -4 && yd == -4){
        this->BlackPawns.SetOff(xs,ys);
        this->BlackKnights.SetOn(xs,ys);
      }
      this->player = 'w';
    }
    this->promote = false;
    return;
  }
}
void Chess::Move(int xs,int ys, int xd, int yd){

  if(this->promote){Promote(xs,ys,xd,yd);
  return;}

  if( player == 'w' ){

    if(this->WhiteKing.IsSet(xs,ys) && this->WhiteKingMoves(xs,ys).IsSet(xd,yd) ){
      this->WhiteKing.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->WhiteKing.SetOn(xd,yd);
    }
    else if(this->WhiteQueen.IsSet(xs,ys) && this->WhiteQueenMoves(xs,ys).IsSet(xd,yd)){
      this->WhiteQueen.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->WhiteQueen.SetOn(xd,yd);
    }
    else if(this->WhitePawns.IsSet(xs,ys) && this->WhitePawnMoves(xs,ys).IsSet(xd,yd)){

      if(UnMovedWhitePawns.IsSet(xs,ys)){
        UnMovedWhitePawns.SetOff(xs,ys);
        UnMovedWhitePawns.SetOn(xs,ys-1);
      }
      if(this->UnMovedBlackPawns.IsSet(xd,yd)){
        RemovePiece(xd,3,this->player);
      }
      this->WhitePawns.SetOff(xs,ys);
      RemovePiece(xd,yd,this->player);
      this->WhitePawns.SetOn(xd,yd);
      if(yd == 0){
        this->promote = true;
        return;
      }
    }
    else if(this->WhiteBishops.IsSet(xs,ys) && this->WhiteBishopMoves(xs,ys).IsSet(xd,yd)){
      this->WhiteBishops.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->WhiteBishops.SetOn(xd,yd);
    }
    else if(this->WhiteKnights.IsSet(xs,ys) && this->WhiteKnightMoves(xs,ys).IsSet(xd,yd)){
      this->WhiteKnights.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->WhiteKnights.SetOn(xd,yd);
    }
    else if(this->WhiteRooks.IsSet(xs,ys) && this->WhiteRookMoves(xs,ys).IsSet(xd,yd)){
      this->WhiteRooks.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->WhiteRooks.SetOn(xd,yd);
    }
    else{
      std::cout<<"Nothing here \n";
    }
    this->player = 'b';
    UnMovedBlackPawns.SetOffRank(1);
  }
  else if( player == 'b'){
    if(this->BlackKing.IsSet(xs,ys)  && this->BlackKingMoves(xs,ys).IsSet(xd,yd)){
      this->BlackKing.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->BlackKing.SetOn(xd,yd);
    }
    else if(this->BlackQueen.IsSet(xs,ys)&& this->BlackQueenMoves(xs,ys).IsSet(xd,yd)){
      this->BlackQueen.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->BlackQueen.SetOn(xd,yd);
    }
    else if(this->BlackPawns.IsSet(xs,ys)&& this->BlackPawnMoves(xs,ys).IsSet(xd,yd)){
      if(UnMovedBlackPawns.IsSet(xs,ys)){
        UnMovedBlackPawns.SetOff(xs,ys);
        UnMovedBlackPawns.SetOn(xs,ys+ 1);
      }

      this->BlackPawns.SetOff(xs,ys);
      if(this->UnMovedWhitePawns.IsSet(xd,yd)){
        RemovePiece(xd,5,player);
      }
      RemovePiece(xd,yd,player);
      this->BlackPawns.SetOn(xd,yd);
      if(yd == 7){
        this->promote = true;
        return;
      }
    }
    else if(this->BlackBishops.IsSet(xs,ys) && this->BlackBishopMoves(xs,ys).IsSet(xd,yd)){

      this->BlackBishops.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->BlackBishops.SetOn(xd,yd);
    }
    else if(this->BlackKnights.IsSet(xs,ys)&& this->BlackKnightMoves(xs,ys).IsSet(xd,yd)){
      this->BlackKnights.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->BlackKnights.SetOn(xd,yd);
    }
    else if(this->BlackRooks.IsSet(xs,ys)&& this->BlackRookMoves(xs,ys).IsSet(xd,yd)){

      this->BlackRooks.SetOff(xs,ys);
      RemovePiece(xd,yd,player);
      this->BlackRooks.SetOn(xd,yd);
    }
    else{
      std::cout<<"Nothing here \n";
    }
    this->player= 'w';
    UnMovedWhitePawns.SetOffRank(6);

  }
  Update();
}
void Chess::PrintBoard(){

  //std::cout<<"\033[0;31m" <<board[i][j].piece.rep<<"\033[0m" <<"\t";
  //std::cout<<"\033[0;34m"<<board[i][j].piece.rep<<"\033[0m"<<"\t"

  for(int j= 0; j<8;j++){
    //std::cout<<'\t'<<(char)(j+65)<<'\t';
  }
  //std::cout<<'\n';
  for(int j= 0; j<8;j++){
    //std::cout<<'\t'<<(j+1)<<"\t";
    for(int i=0; i<8; i++){

      if ( BlackPawns.IsSet(i,j)){
        std::cout<<'P';
        //std::cout<<"\t\033[0;34m"<<"P"<<"\033[0m"<<"\t";
      }
      else if(WhitePawns.IsSet(i,j)){
        std::cout<<'p';
        //std::cout<<"\t\033[0;31m" <<"P"<<"\033[0m" <<"\t";
      }
      else if(BlackKing.IsSet(i,j)){
        std::cout<<'K';
      //std::cout<<"\t\033[0;34m"<<"K"<<"\033[0m"<<"\t";
      }
      else if(WhiteKing.IsSet(i,j)){
        std::cout<<'k';
        //std::cout<<"\t\033[0;31m" <<"K"<<"\033[0m" <<"\t";
      }
      else if(BlackQueen.IsSet(i,j)){
        std::cout<<'Q';
        //std::cout<<"\t\033[0;34m"<<"Q"<<"\033[0m"<<"\t";
      }
      else if(WhiteQueen.IsSet(i,j)){
        std::cout<<'q';
        //std::cout<<"\t\033[0;31m" <<"Q"<<"\033[0m" <<"\t";
      }
      else if(BlackRooks.IsSet(i,j)){
        std::cout<<'R';
      //  std::cout<<"\t\033[0;34m"<<"R"<<"\033[0m"<<"\t";
      }
      else if(WhiteRooks.IsSet(i,j)){
        std::cout<<'r';
        //std::cout<<"\t\033[0;31m" <<"R"<<"\033[0m" <<"\t";
      }
      else if(BlackBishops.IsSet(i,j)){
        std::cout<<'B';
        //std::cout<<"\t\033[0;34m"<<"B"<<"\033[0m"<<"\t";
      }
      else if(WhiteBishops.IsSet(i,j)){
        std::cout<<'b';
      //  std::cout<<"\t\033[0;31m" <<"B"<<"\033[0m" <<"\t";
      }
      else if(BlackKnights.IsSet(i,j)){
        std::cout<<'N';
      //  std::cout<<"\t\033[0;34m"<<"N"<<"\033[0m"<<"\t";
      }
      else if(WhiteKnights.IsSet(i,j)){
        std::cout<<'n';
      //  std::cout<<"\t\033[0;31m" <<"N"<<"\033[0m" <<"\t";
      }
      else{
        std::cout<<"X";
      //  std::cout<<"\tX\t";
      }

    }
    //std::cout << '\n'<<'\n';
  }
  //std::cout << '\n';

}
void Chess::PrintBoard(bool debug){
  if(debug){
    std::cout<<"\033[0;31m" <<board[i][j].piece.rep<<"\033[0m" <<"\t";
    std::cout<<"\033[0;34m"<<board[i][j].piece.rep<<"\033[0m"<<"\t"

    for(int j= 0; j<8;j++){
      std::cout<<'\t'<<(char)(j+65)<<'\t';
    }
    std::cout<<'\n';
    for(int j= 0; j<8;j++){
      std::cout<<'\t'<<(j+1)<<"\t";
      for(int i=0; i<8; i++){

        if ( BlackPawns.IsSet(i,j)){
          //std::cout<<'P';
          std::cout<<"\t\033[0;34m"<<"P"<<"\033[0m"<<"\t";
        }
        else if(WhitePawns.IsSet(i,j)){
          //std::cout<<'p';
          std::cout<<"\t\033[0;31m" <<"P"<<"\033[0m" <<"\t";
        }
        else if(BlackKing.IsSet(i,j)){
          //std::cout<<'K';
          std::cout<<"\t\033[0;34m"<<"K"<<"\033[0m"<<"\t";
        }
        else if(WhiteKing.IsSet(i,j)){
          //std::cout<<'k';
          std::cout<<"\t\033[0;31m" <<"K"<<"\033[0m" <<"\t";
        }
        else if(BlackQueen.IsSet(i,j)){
          //std::cout<<'Q';
          std::cout<<"\t\033[0;34m"<<"Q"<<"\033[0m"<<"\t";
        }
        else if(WhiteQueen.IsSet(i,j)){
          //std::cout<<'q';
          std::cout<<"\t\033[0;31m" <<"Q"<<"\033[0m" <<"\t";
        }
        else if(BlackRooks.IsSet(i,j)){
          //std::cout<<'R';
          std::cout<<"\t\033[0;34m"<<"R"<<"\033[0m"<<"\t";
        }
        else if(WhiteRooks.IsSet(i,j)){
          //std::cout<<'r';
          std::cout<<"\t\033[0;31m" <<"R"<<"\033[0m" <<"\t";
        }
        else if(BlackBishops.IsSet(i,j)){
          //std::cout<<'B';
          std::cout<<"\t\033[0;34m"<<"B"<<"\033[0m"<<"\t";
        }
        else if(WhiteBishops.IsSet(i,j)){
          //std::cout<<'b';
          std::cout<<"\t\033[0;31m" <<"B"<<"\033[0m" <<"\t";
        }
        else if(BlackKnights.IsSet(i,j)){
          //std::cout<<'N';
          std::cout<<"\t\033[0;34m"<<"N"<<"\033[0m"<<"\t";
        }
        else if(WhiteKnights.IsSet(i,j)){
          //std::cout<<'n';
          std::cout<<"\t\033[0;31m" <<"N"<<"\033[0m" <<"\t";
        }
        else{
          //std::cout<<"X";
          std::cout<<"\tX\t";
        }

      }
      //std::cout << '\n'<<'\n';
    }
    //std::cout << '\n';

  }
}
Chess * Chess::Copy(){
  Chess C;
  C.board = this->board;

  C.WhitePawns = this->WhitePawns;
  C.BlackPawns = this->BlackPawns;

  C.WhiteKnights = this->WhiteKnights;
  C.BlackKnights = this->BlackKnights;

  C.WhiteBishops = this->WhiteBishops;
  C.BlackBishops = this->BlackBishops;

  C.WhiteRooks = this->WhiteRooks;
  C.BlackRooks = this->BlackRooks;

  C.WhiteQueen = this->WhiteQueen;
  C.BlackQueen = this->BlackQueen;

  C.WhiteKing = this->WhiteKing;
  C.BlackKing =this->BlackKing;

  C.WhitePieces = this->WhitePieces;
  C.BlackPieces = this->BlackPieces;

  C.WhiteAttacks = this->WhiteAttacks;
  C.BlackAttacks = this->BlackAttacks;

  C.UnMovedBlackPawns = this->UnMovedBlackPawns;
  C.UnMovedWhitePawns = this->UnMovedWhitePawns;


  return C*;


}
