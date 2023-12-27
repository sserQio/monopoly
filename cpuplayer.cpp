#include "cpuplayer.h"


//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

bool CPUPlayer::buy_land(int cost){
    int temp = Player::random(max_value);

    //if (cost <= Player::get_budget() && temp == 1){
        return Player::buy_land(cost);
}


bool CPUPlayer::buy_house (int cost){
    int temp = Player::random(n);
    bool state = //se possiedo la casella e non ho casa/albergo 
    //if (state && temp == 1){
        return Player::buy_house(cost);
    //}
}


bool CPUPlayer::buy_hotel(int cost){
    int temp = Player::random(n);
    bool state = //se possiedo la casella e ho casa 
    //if (state && temp == 1){
        return Player::buy_hotel(cost);
    //}

}


int CPUPlayer::random_num(int max_value){ 
    int n;
    double x;
    double y = RAND_MAX;
    while (true){
        x = std::rand();
        if (x != y){break;}
    }
    n = (int)((x/y) * max_value);
    return n;
}