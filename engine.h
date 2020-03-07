#ifndef __ENGINE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ENGINE_H_INCLUDED__
#include "chess.h"
#include <iostream>
#include <list>
class Node{
  public:
    Board B;
    float value;
    Node *parent = NULL;
    Node(Board b);
    Node(Board b,Node *p);
    ~Node();
    list <Node *> children;
    void genChildren();
    //Node * bestChoice(); // gets best choice at a given points
};
int pieceEval(char rep);
float heuristic(Node *N);
float alphabeta(Node *N, int depth, float alpha, float beta, bool maximizingPlayer);
bool center4(int i,int j);
bool outer4(int i,int j);
float min(float x,float y);
float max(float x,float y);
#endif
