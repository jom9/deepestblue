#include "Chess.h"
#include "CreateGame.h"
#include <iostream>
#include <fstream>

#include<string.h>

using namespace std;

void CreateGame::GetGameFromCache(int xs,int ys, int xd,int yd){
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
  outfile << '('<<xs<<','<<ys<<','<<xd<<','<<yd<<')'<<'\n';
  outfile.close();
  C.Move(xs,ys,xd,yd);
  C.PrintBoard();
}

void CreateGame::EmptyCache(){
  string line;
  ofstream myfile ("GameCache.txt",ios::trunc);

}

int main(int argc,char ** argv){
  CreateGame C;
  int xs,ys,xd,yd;
  xs = argv[2][0] -48;
  ys = argv[3][0] -48;
  xd = argv[4][0] -48;
  yd = argv[5][0] -48;
  cout<<xs<<ys<<"\n";
  if(strcmp(argv[1], "new") == 0){ // clear cache
    C.EmptyCache();
    C.GetGameFromCache(xs,ys,xd,yd);
  }
  else if(strcmp(argv[1] , "cache") == 0){
    C.GetGameFromCache(xs,ys,xd,yd);
  }else{
    cout<<"error\n";
  }



}
