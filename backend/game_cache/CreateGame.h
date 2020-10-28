#ifndef CREATEGAME_H
#define CREATEGAME_H
#include<stdio.h>
#include "../logic/Chess.h"



class CreateGame{
public:
  Chess GetGameFromCache(int xs,int ys, int xd,int yd);
  void EmptyCache();
  static Chess*  GetGameFromString(char *s,char player);
};

#endif
