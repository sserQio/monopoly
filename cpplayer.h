#ifndef CPU_H
#define CPU_H

#include "player.cpp"

class Cpu : public Player{
    
    virtual void buy_land(int cost);
    virtual void buy_house (int cost);
    virtual void buy_hotel(int cost);

};





#endif //CPU_H