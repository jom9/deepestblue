#include "../logic/Chess.h"
#include "../logic/BitBoard.h"


class Heuristic{
  public:
    Chess Game;
    Heuristic(Chess C);
    float attacks();
    float material();
    float eval();
};
