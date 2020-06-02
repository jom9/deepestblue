

#include "../logic/Chess.h"
#include "CreateGame.h"
#include <iostream>
#include <fstream>

#include<string.h>

using namespace std;

Chess CreateGame::GetGameFromCache(int xs,int ys, int xd,int yd){
  Chess C;
  C.StartGame();
  int cxs,cys,cxd,cyd;
  string line;
  ifstream myfile ("GameCache.txt");
  if (myfile.is_open())
  {

    while ( getline (myfile,line) )
    { //01234567
      //(1,1,1,1)
      cxs = line.at(1) -48;
      cys = line.at(3)-48;
      cxd = line.at(5)-48;
      cyd = line.at(7)-48;
      C.Move(cxs,cys,cxd,cyd);
      //cout << line << '\n';
    }

    myfile.close();

  }else{ cout << "Unable to open file";}
  ofstream outfile;
  outfile.open ("GameCache.txt",ios::app);
  try{


  C.Move(xs,ys,xd,yd);
  C.PrintBoard();
  outfile << '('<<xs<<','<<ys<<','<<xd<<','<<yd<<')'<<'\n';}
  catch (InvalidMove &E){
      cout<<"InvalidMove";
  }
  outfile.close();
  return C;
}

void CreateGame::EmptyCache(){
  string line;
  ofstream myfile ("GameCache.txt",ios::trunc);

}
Chess * CreateGame::GetGameFromString(char * s,char player){
  Chess *C = new Chess();
  C->player = player;
  for(int j=0;j<8;j++){
    for(int i =0; i<8;i++){
      switch(s[i+8*j]){
        case 'P':
          if(j==1){C->UnMovedBlackPawns.SetOn(i,j);}
          C->BlackPawns.SetOn(i,j);
          C->BlackPieces.SetOn(i,j);
          break;
        case 'p':
          if(j==6){C->UnMovedWhitePawns.SetOn(i,j);}
          C->WhitePawns.SetOn(i,j);
          C->WhitePieces.SetOn(i,j);
          break;
        case 'K':
          C->BlackPieces.SetOn(i,j);
          C->BlackKing.SetOn(i,j);
          break;
        case 'k':
          C->WhitePieces.SetOn(i,j);
          C->WhiteKing.SetOn(i,j);
          break;
        case 'N':
          C->BlackPieces.SetOn(i,j);
          C->BlackKingMoves(i,j);
          break;
        case 'n':
          C->WhitePieces.SetOn(i,j);
          C->WhiteKnights.SetOn(i,j);
          break;
        case 'R':
          C->BlackPieces.SetOn(i,j);
          C->BlackRooks.SetOn(i,j);
          break;
        case 'r':
          C->WhitePieces.SetOn(i,j);
          C->WhiteRooks.SetOn(i,j);
          break;
        case 'B':
          C->BlackPieces.SetOn(i,j);
          C->BlackBishops.SetOn(i,j);
          break;
        case 'b':
          C->WhitePieces.SetOn(i,j);
          C->WhiteBishops.SetOn(i,j);
          break;
        case 'Q':
          C->BlackPieces.SetOn(i,j);
          C->BlackQueen.SetOn(i,j);
          break;
        case 'q':
          C->WhitePieces.SetOn(i,j);
          C->WhiteQueen.SetOn(i,j);
          break;
      }
    }
  }
return C;
}
