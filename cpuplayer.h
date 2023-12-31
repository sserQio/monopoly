#ifndef CPU_H
#define CPU_H

#include "player.h"

class CPUPlayer: public Player{

    public:
        CPUPlayer() : Player(){     name = "CPU" + name;};
        CPUPlayer(std::string word) : Player(){     name = word;};

        virtual bool interactions(){    return false;};
        virtual purchase buy_land(int cost);
        virtual purchase buy_house (int cost);
        virtual purchase buy_hotel(int cost);

};





#endif //CPU_H