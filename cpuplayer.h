#ifndef CPU_H
#define CPU_H

#include "player.cpp"

class CPUPlayer: public Player{

    public:
        CPUPlayer() : Player(){};
        CPUPlayer(std::string name) : Player(){     name = "CPU"+name;};

        virtual purchase buy_land(int cost);
        virtual purchase buy_house (int cost);
        virtual purchase buy_hotel(int cost);

};





#endif //CPU_H