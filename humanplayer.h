#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.cpp"

class HumanPlayer : public Player{
    private: 
        bool ask_input(int cost);
    public:
        HumanPlayer() : Player(){};
        HumanPlayer(std::string name) : Player(){   name = "Human"+name;};

        virtual bool buy_land(int cost);
        virtual bool buy_house(int cost);
        virtual bool buy_hotel(int cost);

};

#endif //HUMANPLAYER_H