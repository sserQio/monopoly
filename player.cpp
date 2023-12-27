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
        if (pos[0] == 0)    budget+=b.start_increment();  //sono passato per il via
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
        if (pos[1] == 0)    budget+=b.start_increment(); //sono passato per il via
        pos[1]+=1;
    }

    if(n > 0)   move(b, n);
}

bool Player::buy_land(int c){ 
    if (budget < c)     return false;
    //altrimenti
    budget -= c;
    lands.push_back(to_string(Board::rows(pos[0])) += (char)pos[1]);
    return true;
}

bool Player::buy_house(int c){ 
    if (budget < c)     return false;

    budget -= c;
    houses.push_back(to_string(Board::rows(pos[0])) += (char)pos[1]);
    return true;
    //rimuovere dai terreni? decidere politiche di stampa proprietà
}

bool Player::buy_hotel(int c){
    if (budget < c)     return false;

    budget -= c;
    hotels.push_back(to_string(Board::rows(pos[0])) += (char)pos[1]);
    return true;
    //rimuovere dalle case? decidere politiche di stampa proprietà
}


//   ---  FUNZIONI DI ACCESSO  ---

std::string Player::get_name(){
    return name;
}

void Player::set_name(std::string word){
    name = word; 
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

