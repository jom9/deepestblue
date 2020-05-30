#include "Chess.h"
#include "BitBoard.h"
#include "Heuristic.h"
class Node{
  public:
    float val;
    Chess Game;
    Node * Parent;
    std::List<Node *> Children;
};
class Engine{
  public:
    Engine(Chess G);
    Node
    std::string SuggestMove();

};
