#ifndef __BITBOARD_H_INCLUDED__
#define __BITBOARD_H_INCLUDED__

#include <bitset>
#include <cassert>
#include<stdio.h>


class BitBoard{
  private:
    std::bitset<64> board;
  public:
    std::bitset<64> GetBoard();
    void SetAll(bool val);
    void SetOn(int x,int y);
    void SetOff(int x,int y);
    void SetOffRank(int r);
    bool IsSet(int x,int y);
    bool CombineXOR(BitBoard B );
    int Count();
    void PrintBoard();

    static bool Inside(int x,int y);
    static BitBoard Or(BitBoard B1, BitBoard B2);
    static BitBoard And(BitBoard B1, BitBoard B2);
    char Rep(int x, int y);

};
#endif
