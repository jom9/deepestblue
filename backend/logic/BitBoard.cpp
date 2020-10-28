

#include "BitBoard.h"
#include<stdio.h>
#include <exception>
#include <iostream>

void BitBoard::SetAll(bool val){
  if(val)
      board.set();   //All bits on
  else
      board.reset(); //All bits off
}
void BitBoard::SetOn(int x, int y){

  if(!this->IsSet(x,y)){
      this->board[(x+8*y)] =1 ;
  }
  else{
    std::cout<<x<<y;
    //throw std::logic_error("error message");
    std::cout << "Something's Here" << '\n';
  }
}
void BitBoard::SetOff(int x,int y){
  //std::cout<<x<<y<<'\n';
  if(this->IsSet(x,y)){
      this->board[(x+8*y)]= 0 ;
  }
  else{
    std::cout << "Nothing's Here" << '\n';
  }
}
void BitBoard::SetOffRank(int r){
  int i;

  for (i =0;i<8;i++){
    this->board[(i+8*r)]= 0 ;
  }
}
bool BitBoard::IsSet(int x,int y){
  return this->board.test((x+8*y));
}
std::bitset<64> BitBoard::GetBoard(){
  return this->board;
}
char BitBoard::Rep(int x, int y){
  return 'X';
}
 BitBoard BitBoard::And(BitBoard B1, BitBoard B2){
  BitBoard B;
  B.board = B1.GetBoard()& B2.GetBoard();
  return B;
}
BitBoard BitBoard::Or(BitBoard B1, BitBoard B2){
  BitBoard B;
  B.board = B1.GetBoard()| B2.GetBoard();
  return B;
}
bool BitBoard::Inside(int x,int y){
  return x<8 && y<8 && x>=0 && y>=0;
}
int BitBoard::Count(){
  return this->board.count();
}
void BitBoard::PrintBoard(){
  std::cout << '\n'<<'\n';
  for(int j= 0; j<8;j++){
    std::cout<<' '<<(j+1)<<" ";
    for(int i=0; i<8; i++){
      if(this->IsSet(i,j)){
        std::cout<<' '<<'X'<<' ';
      }else{
        std::cout<<' '<<'0'<<' ';
      }


    }
    std::cout << '\n'<<'\n';
  }
  std::cout << '\n'<<'\n';
}
