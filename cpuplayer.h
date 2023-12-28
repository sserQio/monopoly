#ifndef CPU_H
#define CPU_H

#include "player.cpp"

class CPUPlayer: public Player{

    public:
        CPUPlayer() : Player(){};
        CPUPlayer(std::string name) : Player(){     name = "CPU"+name;};

        virtual bool buy_land(int cost);
        virtual bool buy_house (int cost);
        virtual bool buy_hotel(int cost);

};





#endif //CPU_H