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
  if(depth==0 && node->children.empty()){
    return heuristic(node);
  }
  if(maximizingPlayer){
    value = -Inf;
    cout<<"gen test\n";
    node->genChildren();
    cout<<"gen test\n";
    //for(list<tuple <int,int>>::iterator it1=blackPos.begin(); it1 != blackPos.end(); ++it1){
    for(list<Node *>::iterator it=node->children.begin(); it!=node->children.end(); ++it){
      Node * child = *it;
      value = max(value, alphabeta(child,  depth-1,  alpha,beta  ,false));
      alpha = max(alpha,value);
      if(alpha>=beta){
        break;
      }
    }
  }
  else{
    value = Inf;
    node->genChildren();
    for(list<Node *>::iterator it=node->children.begin(); it!=node->children.end(); ++it){
      Node * child = *it;
      value = min(value, alphabeta(child,  depth-1,  alpha,beta,  true));
      beta = min(alpha,value);
      if(alpha>=beta){
        break;
      }
    }

  }
  return value;
}
Node::Node(Board b){this->B=b;}
void Node::genChildren(){
  list<tuple <int,int,int,int>> moves = B.legalMoves();
  for(list<tuple <int,int,int,int>>::iterator it=moves.begin(); it != moves.end(); ++it){
    int xs,ys,xd,yd;
    xs=get<0>(*it);
    ys=get<1>(*it);
    xd=get<2>(*it);
    yd=get<3>(*it);
    cout<<"Child:\t"<<xs<<'\t'<<ys<<'\t'<<xd<<'\t'<<yd<<"\n";
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
  return val;
}

int main(int argc, char *argv[]){
  int depth = 10;
  if(argc >1){
    cout<<"test\n";

    Board b;
    b.takeMove(4,1,4,3);
    b.takeMove(4,6,4,4);
    b.printBoard();
    int xs,ys,xd,yd;
                  //0123456
    char move[7];///4X4X4X4

    while(true){
      Node N(b);
      cout<<"Testq\n";
      alphabeta(&N,depth,Inf,-Inf,true);
      cout<<"Testq\n";
      Node *bestMove = N.bestChoice();
      b= bestMove->B;
      b.printBoard();
      cout<<"Enter Move";
      cin>>move;
      xs = (int)move[0];
      ys = (int)move[2];
      xd = (int)move[4];
      yd = (int)move[6];
      b.takeMove(xs,ys,xd,yd);
      b.printBoard();

    }


  }

}
