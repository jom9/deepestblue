#include "Chess.h"
#include "BitBoard.h"
#include "Heuristic.h"


class Heuristic{
  public:
    Chess Game;
    Heuristic(Chess C);
    float attacks();
    float material();
    float eval();
};
