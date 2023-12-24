#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdlib> 
#include <ctime>

class Board;

class Player{

    protected: 
        //Da spostare in Board? Ottimizzare per tabelloni di altre dimensioni?
        int budget;
        int pos[2];

        std::vector<std::string> houses; //lista delle coordinate delle case in possesso
        std::vector<std::string> hotels;
        std::vector<std::string> lands;
        void move(Board& board, int times); 

    public:
        int throw_dice();
        int get_budget();
        int* get_pos();

        virtual void buy_land(int cost);
        virtual void buy_house (int cost);
        virtual void buy_hotel(int cost);

        const std::vector<std::string>& get_houses(); //meglio restituire una copia modificabile?
        const std::vector<std::string>& get_hotels();
        const std::vector<std::string>& get_lands();

};

#endif //PLAYER_H
