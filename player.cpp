#include "player.h"
#include "board.h"

//   ---  COSTRUTTORI  ---


//   ---  FUNZIONI DI GIOCO  ---

int Player::throw_dice(){
    srand(time(0));
    return ((rand()%6)+1 + (rand()%6)+1);
}

void Player::move(Board& b, int n){
    while(pos[1] == 0 && pos[0] >= 0 && n>0){
        n--;
        pos[0]-=1;
    }
    while(pos[1] == b.get_width() -1 && pos[0] < b.get_height() && n>0){ //pos[0] partirà al massimo da HEIGHT -1
        n--;
        pos[0]+=1;
    }
    while(pos[0] == b.get_height() -1 && pos[1] >= 0 && n>0){
        n--;
        pos[1]-=1;
    }
    while(pos[0] == 0 && pos[1] < b.get_width() -1 && n>0){
        n--;
        pos[1]+=1;
    }

    if(n > 0)   move(b, n);
}

void Player::buy_land(int c){ //aggiungere richiesta input o creare altra derivata HumanPlayer
    if (budget < c){
        std::cout <<"Il giocatore non possiede finanze sufficienti per l'acquisto" <<"\n";
        return;
    }
    //altrimenti
    budget -= c;
    lands.push_back(to_string(columns(pos[0])) += (char)pos[1]);
}

void Player::buy_house(int c){ //aggiungere richiesta input o creare altra derivata HumanPlayer
    if (budget < c){
        std::cout <<"Il giocatore non possiede finanze sufficienti per l'acquisto" <<"\n";
        return;
    }
    budget -= c;
    houses.push_back(to_string(columns(pos[0])) += (char)pos[1]);
    //rimuovere dai terreni? decidere politiche di stampa proprietà
}

void Player::buy_house(int c){ //aggiungere richiesta input o creare altra derivata HumanPlayer

    if (budget < c){
        std::cout <<"Il giocatore non possiede finanze sufficienti per l'acquisto" <<"\n";
        return;
    }
    budget -= c;
    hotels.push_back(to_string(columns(pos[0])) += (char)pos[1]);
    //rimuovere dalle case? decidere politiche di stampa proprietà
}


//   ---  FUNZIONI DI ACCESSO  ---

std::string Player::get_name(){
    return name;
}

void Player::set_name(std::string word){
    name = name;
}

int Player::get_budget(){
    return budget;
}

int* Player::get_pos(){
    return pos;
}

const std::vector<std::string>& Player::get_lands(){
    return lands;
}

const std::vector<std::string>& Player::get_houses(){
    return houses;
}

const std::vector<std::string>& Player::get_hotels(){
    return hotels;
}

