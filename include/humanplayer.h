// Autore e Matricola: Sergio Petenazzo, 2066693

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "../include/player.h"

class HumanPlayer : public Player{
    private: 
        bool ask_input(int cost);
    public:
        HumanPlayer() : Player(){   name = "Human"+name;};
        HumanPlayer(std::string word) : Player(){   name = word;};

        virtual bool interactions(){    return true;};
        virtual purchase buy_land(int cost);
        virtual purchase buy_house(int cost);
        virtual purchase buy_hotel(int cost);

};

#endif //HUMANPLAYER_H