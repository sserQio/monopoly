#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.cpp"

class HumanPlayer : public Player{
    private: 
        bool ask_input(int cost);
    public:
        HumanPlayer() : Player(){};
        HumanPlayer(std::string name) : Player(){   name = "Human"+name;};

        virtual purchase buy_land(int cost);
        virtual purchase buy_house(int cost);
        virtual purchase buy_hotel(int cost);

};

#endif //HUMANPLAYER_H