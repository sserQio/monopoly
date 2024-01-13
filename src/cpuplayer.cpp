// Autore e Matricola: Alberto Barbieri, 2066682

#include "../include/cpuplayer.h"


//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

Player::purchase CPUPlayer::buy_land(int cost){
    //srand(time(0)) delego a board l'inizializzazione del seed per non inficiare la (pseudo) randomicità

    int i = rand()%4;
 
    if (i == 0) return Player::buy_land(cost);
    return purchase::NOT_DONE;
}


Player::purchase CPUPlayer::buy_house(int cost){
    int i = rand()%4;
 
    if (i == 0) return Player::buy_house(cost);
    return purchase::NOT_DONE;
}


Player::purchase CPUPlayer::buy_hotel(int cost){
    int i = rand()%4;
 
    if (i == 0) return Player::buy_hotel(cost);
    return purchase::NOT_DONE;
}


