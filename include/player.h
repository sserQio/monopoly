#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdlib> 
#include <ctime>

class Board;

class Player{
    protected: 
        std::string name;
        int budget;
        int pos[2];

        std::vector<std::string> houses; //lista delle coordinate delle case in possesso
        std::vector<std::string> hotels;
        std::vector<std::string> lands;

    public:
        Player() : budget(100), name("Player"){ pos[0] = 0, pos[1] = 0;}; 

        int throw_dice();
        int get_budget();
        int* get_pos();

        std::string get_name();
        void set_name(std::string name);
        void set_budget(int n);

        void move(Board& board, int times); 

        //restituisce true solo se è un tipo di giocatore che può avere interazione via terminale
        //(nel nostro caso solamente HumanPlayer, ma può dipendere dall'implementazione)
        virtual bool interactions(){    return false;}; 

        enum class purchase {DONE, OUT_OF_BALANCE, NOT_DONE};   
        virtual purchase buy_land(int cost);
        virtual purchase buy_house (int cost);
        virtual purchase buy_hotel(int cost);

        int pay(Player& p2, int cost); //restituisce il nuovo budget del giocatore pagante

        const std::vector<std::string>& get_houses(); //meglio restituire una copia modificabile?
        const std::vector<std::string>& get_hotels();
        const std::vector<std::string>& get_lands();

        class Invalid_Budget{};
};

#endif //PLAYER_H
