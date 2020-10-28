
#include "CreateGame.h"
#include <iostream>
#include<string.h>

using namespace std;
int main(int argc,char ** argv){
  CreateGame C;
  int xs,ys,xd,yd;
  xs = argv[2][0] -48;
  ys = argv[3][0] -48;
  xd = argv[4][0] -48;
  yd = argv[5][0] -48;
  //cout<<xs<<ys<<"\n";
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
