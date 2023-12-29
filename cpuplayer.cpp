#include "cpuplayer.h"


//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

Player::purchase CPUPlayer::buy_land(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return Player::buy_land(cost);
    return purchase::NOT_DONE;
}


Player::purchase CPUPlayer::buy_house(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return Player::buy_house(cost);
    return purchase::NOT_DONE;
}


Player::purchase CPUPlayer::buy_hotel(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return Player::buy_hotel(cost);
    return purchase::NOT_DONE;
}


