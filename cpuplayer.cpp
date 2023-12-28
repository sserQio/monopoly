#include "cpuplayer.h"


//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

bool CPUPlayer::buy_land(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return buy_land(cost);
    return false;
}


bool CPUPlayer::buy_house(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return buy_house(cost);
    return false;
}


bool CPUPlayer::buy_hotel(int cost){
    srand(time(0));
    int i = rand()%4;
 
    if (i == 0) return buy_hotel(cost);
    return false;
}


