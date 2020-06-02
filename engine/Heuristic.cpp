#include "Heuristic.h"




float Heuristic::attacks(){
  return 0;
}

float Heuristic::material(){
  float s = 0;
  s+=Game.WhitePawns.Count();
  s-=Game.BlackPawns.Count();

  s+=3*Game.WhiteKnights.Count();
  s-=3*Game.BlackKnights.Count();

  s+=3*Game.WhiteBishops.Count();
  s-=3*Game.BlackBishops.Count();

  s+=3*Game.WhiteRooks.Count();
  s-=3*Game.BlackRooks.Count();

  s+=3*Game.WhiteQueen.Count();
  s-=Game.BlackQueen.Count();

  s+=3*Game.WhiteKing.Count();
  s-=3*Game.BlackKing.Count();
}

float Heuristic::eval(){
  float s = 0;
  s+=this->material();
  s+=this->attacks();
  return s;
}

Heuristic::Heuristic(Chess C){
  this->Game = C;
}
