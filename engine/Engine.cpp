#include "Engine.h"
#include <iostream>
Node::Node(Chess * G,int xs,int ys,int xd,int yd){
  this->move = std::make_tuple(xs,ys,xd,yd);
  this->Game = G;
}
void Node::WhitePawnMoves(int x,int y){
  //std::cout<<"PAWN\n";

  if(this->Game->UnMovedWhitePawns.IsSet(x,y)){
    if(!this->Game->WhitePieces.IsSet(x,y-1) && !this->Game->BlackPieces.IsSet(x,y-1)){
        if(!this->Game->WhitePieces.IsSet(x,y-2) && !this->Game->BlackPieces.IsSet(x,y-2)){
        Chess *G  = this->Game->Copy();
        G->Move(x,y,x,y-2);


        Node *Child = new Node(G,x,y,x,y-2);
        Child->Parent = this;
        this->Children.push_back(Child);
      }

    }

  }
  if(BitBoard::Inside(x,y-1)){
    if(!this->Game->WhitePieces.IsSet(x,y-1) && !this->Game->BlackPieces.IsSet(x,y-1)){
      Chess *G = this->Game->Copy();;
      G->Move(x,y,x,y-1);
      Node *Child = new Node(G,x,y,x,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
  }
  if(BitBoard::Inside(x-1,y-1)){
    if(this->Game->BlackPieces.IsSet(x-1,y-1) ){
      Chess *G = this->Game->Copy();
      G->Move(x,y,x-1,y-1);
      Node *Child = new Node(G,x,y,x-1,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
    else if(this->Game->UnMovedBlackPawns.IsSet(x-1,y-1)){
      Chess *G = this->Game->Copy();
      G->Move(x,y,x-1,y-1);
      Node *Child = new Node(G,x,y,x-1,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
  }
  if(BitBoard::Inside(x+1,y-1)){
    if(this->Game->BlackPieces.IsSet(x+1,y-1) ){
      Chess *G = this->Game->Copy();
      G->Move(x,y,x+1,y-1);
      Node *Child = new Node(G,x,y,x+1,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
    else if(this->Game->UnMovedBlackPawns.IsSet(x+1,y-1)){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x+1,y-1);
      Node *Child = new Node(G,x,y,x+1,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
  }
}
void Node::WhiteKnightMoves(int x, int y){
  for(int j = -2; j<3; j++){
    for(int i = -2; i<3; i++){
      if(i==0 || j==0 || (i==j)){
        continue;
      }
      if(BitBoard::Inside(x+i,y+j) && !this->Game->WhitePieces.IsSet(x+i,y+j)){
        //std::cout<<"Knight "<<x+i<<' '<<y+j;
        Chess * G = this->Game->Copy();
        G->Move(x,y,x+i,y+j);
        Node *Child = new Node(G,x,y,x+i,y+j);
        Child->Parent = this;
        this->Children.push_back(Child);
      }
    }
  }
}
void Node::WhiteBishopMoves(int x, int y){
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y+i) && !this->Game->WhitePieces.IsSet(x+i,y+i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y+i);
    Node *Child = new Node(G,x,y,x+i,y+i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->BlackPieces.IsSet(x+i,y+i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y-i) && !this->Game->WhitePieces.IsSet(x-i,y-i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y-i);
    Node *Child = new Node(G,x,y,x-i,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->BlackPieces.IsSet(x-i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x+i,y-i) && !this->Game->WhitePieces.IsSet(x+i,y-i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y-i);
    Node *Child = new Node(G,x,y,x+i,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->BlackPieces.IsSet(x+i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y+i) && !this->Game->WhitePieces.IsSet(x-i,y+i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y+i);
    Node *Child = new Node(G,x,y,x-i,x+i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->BlackPieces.IsSet(x-i,y+i) ){
      break;
    }
    i++;
  }
}
void Node::WhiteRookMoves(int x, int y){
  int i;
  i = 1;

  while(BitBoard::Inside(x+i,y) && !this->Game->WhitePieces.IsSet(x+i,y) ){
    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y);
    Node *Child = new Node(G,x,y,x+i,y);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->BlackPieces.IsSet(x+i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y) && !this->Game->WhitePieces.IsSet(x-i,y) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y);
    Node *Child = new Node(G,x,y,x-i,y);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->BlackPieces.IsSet(x-i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y-i) && !this->Game->WhitePieces.IsSet(x,y-i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x,y-i);
    Node *Child = new Node(G,x,y,x,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->BlackPieces.IsSet(x,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y+i) && !this->Game->WhitePieces.IsSet(x,y+i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x,y+i);
    Node *Child = new Node(G,x,y,x,y+i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->BlackPieces.IsSet(x,y+i) ){
      break;
    }
    i++;
  }
}
void Node::WhiteQueenMoves(int x,int y){
  this->WhiteRookMoves(x,y);
  this->WhiteBishopMoves(x,y);
}
void Node::WhiteKingMoves(int x,int y){
  for(int i=-1; i<2;i++){
    for(int j=-1; j<2;j++){

      if(i==0 || j== 0 || !BitBoard::Inside(x+i,y+j) || this->Game->WhitePieces.IsSet(x+i,y+j)){
        continue;
      }

      if(BitBoard::Inside(x+i,y+j) && !this->Game->WhitePieces.IsSet(x+i,y+j)){
        Chess * G = this->Game->Copy();
        G->Move(x,y,x+i,y+j);
        Node *Child = new Node(G,x,y,x+i,y+j);
        Child->Parent = this;
        this->Children.push_back(Child);
      }

    }
  }
}

void Node::BlackPawnMoves(int x,int y){
  if(this->Game->UnMovedBlackPawns.IsSet(x,y)){
    if(!this->Game->WhitePieces.IsSet(x,y+1)&&!this->Game->WhitePieces.IsSet(x,y+2)){
      if(!this->Game->BlackPieces.IsSet(x,y+1)&&!this->Game->BlackPieces.IsSet(x,y+2)){
        Chess * G = this->Game->Copy();
        G->Move(x,y,x,y+2);
        Node *Child = new Node(G,x,y,x,y+2);
        Child->Parent = this;
        this->Children.push_back(Child);
      }

  }
  }
  if(BitBoard::Inside(x,y+1)){
    if(!this->Game->WhitePieces.IsSet(x,y+1) && !this->Game->BlackPieces.IsSet(x,y+1)){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x,y+1);
      Node *Child = new Node(G,x,y,x,y+1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }

  }
  if(BitBoard::Inside(x-1,y+1)){
    if(this->Game->WhitePieces.IsSet(x-1,y+1) ){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x-1,y+1);
      Node *Child = new Node(G,x,y,x-1,y+1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
    else if(this->Game->UnMovedWhitePawns.IsSet(x-1,y+1)){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x-1,y+1);
      Node *Child = new Node(G,x,y,x-1,y-1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
  }
  if(BitBoard::Inside(x+1,y+1)){
    if(this->Game->WhitePieces.IsSet(x+1,y+1) ){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x+1,y+1);
      Node *Child = new Node(G,x,y,x+1,y+1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
    else if(this->Game->UnMovedWhitePawns.IsSet(x+1,y+1)){
      Chess * G = this->Game->Copy();
      G->Move(x,y,x+1,y+1);
      Node *Child = new Node(G,x,y,x+1,y+1);
      Child->Parent = this;
      this->Children.push_back(Child);
    }
  }
}
void Node::BlackKnightMoves(int x, int y){
  for(int j = -2; j<3; j++){
    for(int i = -2; i<3; i++){
      if(i==0 || j==0 ||(i==j)){
        continue;
      }
      if(BitBoard::Inside(x+i,y+j) && !this->Game->BlackPieces.IsSet(x+i,y+j)){
        Chess * G = this->Game->Copy();
        G->Move(x,y,x+i,y+j);
        Node *Child = new Node(G,x,y,x+i,y+j);
        Child->Parent = this;
        this->Children.push_back(Child);
      }
    }
  }
}
void Node::BlackBishopMoves(int x, int y){
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y+i) && !this->Game->BlackPieces.IsSet(x+i,y+i) ){
    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y+i);
    Node *Child = new Node(G,x,y,x+i,y+i);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x+i,y+i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y-i) && !this->Game->BlackPieces.IsSet(x-i,y-i) ){
    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y-i);
    Node *Child = new Node(G,x,y,x-i,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x-i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x+i,y-i) && !this->Game->BlackPieces.IsSet(x+i,y-i) ){
    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y-i);
    Node *Child = new Node(G,x,y,x+i,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x+i,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y+i) && !this->Game->BlackPieces.IsSet(x-i,y+i) ){
    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y+i);
    Node *Child = new Node(G,x,y,x-i,y+i);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x-i,y+i) ){
      break;
    }
    i++;
  }

}
void Node::BlackRookMoves(int x, int y){
  int i;
  i = 1;
  while(BitBoard::Inside(x+i,y) && !this->Game->BlackPieces.IsSet(x+i,y) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x+i,y);
    Node *Child = new Node(G,x,y,x+i,y);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x+i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x-i,y) && !this->Game->BlackPieces.IsSet(x-i,y) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x-i,y);
    Node *Child = new Node(G,x,y,x-i,y);
    Child->Parent = this;
    this->Children.push_back(Child);
    if( this->Game->WhitePieces.IsSet(x-i,y) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y-i) && !this->Game->BlackPieces.IsSet(x,y-i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x,y-i);
    Node *Child = new Node(G,x,y,x,y-i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->WhitePieces.IsSet(x,y-i) ){
      break;
    }
    i++;
  }
  i = 1;
  while(BitBoard::Inside(x,y+i) && !this->Game->BlackPieces.IsSet(x,y+i) ){

    Chess * G = this->Game->Copy();
    G->Move(x,y,x,y+i);
    Node *Child = new Node(G,x,y,x,y+i);
    Child->Parent = this;
    this->Children.push_back(Child);

    if( this->Game->WhitePieces.IsSet(x,y+i) ){
      break;
    }
    i++;
  }

}
void Node::BlackQueenMoves(int x,int y){
  this->BlackRookMoves(x,y);
  this->BlackBishopMoves(x,y);
}
void Node::BlackKingMoves(int x,int y){
  for(int i=-1; i<2;i++){
    for(int j=-1; j<2;j++){
      if(i==0 || j== 0 || !BitBoard::Inside(x+i,y+i) || this->Game->BlackPieces.IsSet(x+i,y+i)){
        continue;
      }
      if(BitBoard::Inside(x+i,y+j) && !this->Game->BlackPieces.IsSet(x+i,y+j)){
        Chess * G = this->Game->Copy();
        G->Move(x,y,x+i,y+j);
        Node *Child = new Node(G,x,y,x+i,y+j);
        Child->Parent = this;
        this->Children.push_back(Child);
      }

    }
  }
}
void Node::GenChildren(){

  if(this->Game->player == 'b'){
    int i,j;
      for(j=0;j<8;j++){
        for(i=0;i<8;i++){
            //std::cout<<i<<j<<"B TEST\n";
            //this->Game->PrintBoard(true);
            if(this->Game->BlackPieces.IsSet(i,j)){
                if(this->Game->BlackKing.IsSet(i,j)){
                  //std::cout<<'K'<<'\n';
                  this->BlackKingMoves(i,j);
                }
                else if(this->Game->BlackKnights.IsSet(i,j)){
                  //std::cout<<'N'<<'\n';
                  this->BlackKnightMoves(i,j);
                }
                else if(this->Game->BlackRooks.IsSet(i,j)){
                  //std::cout<<'R'<<'\n';
                  this->BlackRookMoves(i,j);
                }
                else if(this->Game->BlackQueen.IsSet(i,j)){
                  //std::cout<<'Q'<<'\n';
                  this->BlackQueenMoves(i,j);
                }
                else if(this->Game->BlackPawns.IsSet(i,j)){
                  //std::cout<<'P'<<'\n';

                  this->BlackPawnMoves(i,j);
                }
            }
        }
      }
  }
  else if(this->Game->player == 'w'){
    int i,j;
      for(j=0;j<8;j++){
        for(i=0;i<8;i++){
            //std::cout<<i<<j<<"W TEST\n";
            //this->Game->PrintBoard(true);
            if(this->Game->WhitePieces.IsSet(i,j)){
              if(this->Game->WhiteKing.IsSet(i,j)){
                //std::cout<<'K'<<'\n';
                this->WhiteKingMoves(i,j);
              }
              else if(this->Game->WhiteKnights.IsSet(i,j)){
                //std::cout<<'N'<<'\n';
                this->WhiteKnightMoves(i,j);
              }
              else if(this->Game->WhiteRooks.IsSet(i,j)){
                //std::cout<<'R'<<'\n';
                this->WhiteRookMoves(i,j);
              }
              else if(this->Game->WhiteQueen.IsSet(i,j)){
                //std::cout<<'Q'<<'\n';
                this->WhiteQueenMoves(i,j);
              }
              else if(this->Game->WhitePawns.IsSet(i,j)){
                //std::cout<<'P'<<'\n';
                this->WhitePawnMoves(i,j);
              }
            }
        }
      }
  }

}


Engine::Engine(Chess G, int depth){
  this->depth = depth;
  this->CurrentGame = G;
}
float Engine::alphabeta(Node *N, int depth, float alpha, float beta, bool maximizingPlayer){
  //N->Game->PrintBoard(true);
  N->GenChildren();
  if(depth == 0 || N->Children.empty()){
    N->Value = Heuristic( *(N->Game) ).eval();
    return N->Value;
  }
  if(maximizingPlayer){
    float value = -10000;
    for(std::list<Node *>::iterator child=N->Children.begin(); child != N->Children.end(); ++child){
      float val = this->alphabeta(*child, depth -1,alpha, beta, false);
      value =  val>value? val:value;
      alpha = alpha>value? alpha: value;
            if(alpha >= beta){break;}// (* β cut-off *)
    }
    N->Value = value;
    return value;
  }
  else{
    float value = 10000;
    for (std::list<Node *>::iterator child=N->Children.begin(); child != N->Children.end(); ++child){
      float val = this->alphabeta(*child,depth - 1,alpha,beta,true);
      value = val>value? value:val;
      beta = beta>value? value:beta;
      if(beta<=alpha){break;}
    }
    N->Value = value;
    return value;
  }
}
void Engine::SuggestMove(){
  try{
  Node * root = new Node( &(this->CurrentGame) ,-1,-1,-1,-1);
  alphabeta(root,this->depth,-10000,10000,true);
  Node* max = new Node(root->Game->Copy(),-1,-1,-1,-1);
  max->Value =-10000000;

  for (std::list<Node * >::iterator child=root->Children.begin(); child != root->Children.end(); ++child){
    //std::cout<<*child<<"\n";
    //(*child)->Game->PrintBoard(true);
    max = max->Value >= (*child)->Value? max: *child;
  }
  //max->Game->PrintBoard(true);
  std::cout<<std::get<0>(max->move)<<' '<<std::get<1>(max->move)<<' '<<std::get<2>(max->move)<<' '<<std::get<3>(max->move);
  }
  catch(std::bad_alloc){
    std::cout<<"OverLoad\n";
  }
}
