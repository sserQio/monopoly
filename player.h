#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
class Player{
    int budget;
    int* pos;

    std::vector<std::string> houses; //lista delle coordinate delle case in possesso
    std::vector<std::string> hotels;
    std::vector<std::string> lands;
    //void move(tabellone per reference); effettua il movimento e chiama check_box

    public:
        int throw_dice();
        int get_budget();
        int* get_pos();

        virtual void buy_land(int cost);
        virtual void buy_house (int cost);
        virtual void buy_hotel(int cost);

        std::vector<std::string> get_houses(); 
        std::vector<std::string> get_hotels();
        std::vector<std::string> get_lands();

};

#endif //PLAYER_H
