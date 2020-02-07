#include "chess.h"
#include "engine.h"
#include <iostream>
int Inf = 100000;

using namespace std;
/*function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            α := max(α, value)
            if α ≥ β then
                break (* β cut-off *)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            β := min(β, value)
            if α ≥ β then
                break (* α cut-off *)
        return value
    */
float alphabeta(Node * node, int depth, float alpha, float beta, bool maximizingPlayer){
  float value;
  node->genChildren();
  cout<<"Is empty?"<<node->children.empty()<<'\n';
  cout<<"depth"<<depth<<"\n";
  if(depth==0 || node->children.empty()){
    value = heuristic(node);
    node->value = value;
    return value;
  }
  if(maximizingPlayer){
    value = -Inf;

    for(list<Node *>::iterator child=node->children.begin(); child!=node->children.end(); ++child){
      cout<<"Depth"<<depth;
      value = max(value, alphabeta(*child,  depth-1,  alpha,beta  ,false));
      alpha = max(alpha,value);
      if(alpha>=beta){
        break;
      }
    }
  }
  else{
    value = Inf;
    for(list<Node *>::iterator child=node->children.begin(); child!=node->children.end(); ++child){

      value = min(value, alphabeta(*child,  depth-1,  alpha,beta,  true));
      beta = min(alpha,value);
      if(alpha>=beta){
        break;
      }
    }

  }
  node->value = value;
  return value;
}
Node::Node(Board b){this->B=b;}
void Node::genChildren(){
  list<tuple <int,int,int,int>> moves = B.legalMoves();
  //cout<<"Parent:\n";
  for(list<tuple <int,int,int,int>>::iterator it=moves.begin(); it != moves.end(); ++it){
    int xs,ys,xd,yd;
    xs=get<0>(*it);
    ys=get<1>(*it);
    xd=get<2>(*it);
    yd=get<3>(*it);
    //cout<<"\tChild:\t"<<xs<<'\t'<<ys<<'\t'<<xd<<'\t'<<yd<<"\n";
    Node *child = new Node(this->B);
    //cout<<"Child:"<<xs<<'\t'<<ys<<'\t'<<xd<<'\t'<<yd<<"\n";
    child->B.takeMove(xs,ys,xd,yd,true);
    children.push_front(child);
  }
}
Node* Node::bestChoice(){
  float max = -Inf;
  Node *N;
  for(list<Node *>::iterator it = children.begin(); it!= children.end(); ++it){
    if( max<(*it)->value ){
      max = (*it)->value;
      N = *it;
    }
  }
  return N;
}
float max(float x,float y){
  if(x>y){
    return x;
  }
  return y;
}
float min(float x,float y){
  if(x<y){
    return x;
  }
  return y;
}

int pointVal(char rep){// returns point values for each piece
  switch(rep){
    case 'X':{return 0;break;}
    case 'P':{return 1;break;}
    case 'N':{return 3;break;}
    case 'B':{return 3;break;}
    case 'R':{return 5;break;}
    case 'Q':{return 9;break;}
  }
  return 0;
}
bool center4(int i,int j){ // center four squares , most important
  if( (i==3 && (j==3||j==4)) || (i==4 && (j==3||j==4)) ){
    return true;
  }
  return false;
}
bool outer4(int i,int j){// outer fours square next important
  if( ( (i==2)&&(j>1&&j<6) ) && ( (i==5)&&(j>1&&j<6) ) && ( (j==2)&&(i>1&&i<6) ) && ( (j==2)&&(i>1&&i<6) )){
    return true;
  }
  return false;
}
float heuristic(Node *N){
  Board Bo = N->B;
  float val =0;
  Square b[8][8] = Bo.board;
  if(Bo.checkmate() && Bo.currentPlayer=='B'){
    return 1000;// if white wins
  }
  else if(Bo.checkmate() && Bo.currentPlayer=='W'){
    return -1000;// if black wins
  }
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      Square S = b[i][j];
      Piece P = S.piece;
      if(P.color=='w'){
        val+=pointVal(P.rep);// checks white material
      }
      else if(P.color=='b'){
        val-=pointVal(P.rep);//checks blacks material
      }
      if(center4(i,j)){
        val+=S.attackedByWhite*.1;
        val-=S.attackedByBlack*.1;
      }
      else if(outer4(i,j)){
        val+=S.attackedByWhite*.05;
        val-=S.attackedByBlack*.05;
      }
      else{
        val+=S.attackedByWhite*.01;
        val-=S.attackedByBlack*.01;
      }


    }
  }
  cout<<"Val:"<<val<<"\n";
  return val;
}

int main(int argc, char **argv){
  int depth =5;
  if(argc >1){
    //depth = (int) argv[1][0];

    cout<<depth<<"test\n";

    Board b;
    b.takeMove(4,1,4,3,true);
    b.takeMove(4,6,4,4,true);
    b.takeMove(6,0,5,2,true);
    b.takeMove(1,7,2,5,true);
    b.takeMove(5,0,2,3,true);
    b.takeMove(6,7,5,5,true);
    b.printBoard();
    int xs,ys,xd,yd;
                  //0123456
    char move[7];///4X4X4X4

    while(true){
      Node N(b);
      alphabeta(&N,depth,-Inf,Inf,true);
      Node *bestMove = N.bestChoice();
      b= bestMove->B;
      b.printBoard();
      cout<<"Enter Move";

      cin>>xs>>ys>>xd>>yd;
      cout<<xs<<ys<<xd<<yd<<"\n";
      b.takeMove(xs,ys,xd,yd);
      b.printBoard();

    }


  }

}
