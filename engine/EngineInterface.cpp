#include "Engine.h";
#include "../GetGame.h"
#include <stdlib.h>

using namespace std;
int main(int argc,char ** argv){
  CreateGame C;
  char player =argv[1][0];
  char* board = argv[3];
  int board = atoi(argv[2]);
  //cout<<xs<<ys<<"\n";
  Chess* C = GetGame.FromString(board,player);




}
int main(){
  Chess C;
  C.StartGame();
  C.Move(4,6,4,4);
  C.Move(4,1,4,3);
  C.Move(6,7,5,5);
  C.Move(6,0,5,2);
  C.Move(6,7,5,5);
  C.Move(6,0,5,2);
  C.PrintBoard(true);
  int depth= 2;
  Engine E(C,depth);

  E.SuggestMove();

}
