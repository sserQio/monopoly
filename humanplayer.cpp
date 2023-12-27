#include "humanplayer.h"

//   ---  FUNZIONI AUSILIARIE  ---

bool HumanPlayer::ask_input(int cost){

    std::cout << "Il budget attuale è di " << budget << " fiorini." <<"\n";
    std::cout << "Si vuole procedere all'acquisto per " << cost <<" fiorini? [y/n] ";
    char c;
    std::cin >> c;
    std::cout <<"\n";

    while (true){
        if (c == 'y' || c == 'Y')   return true;
        else if (c == 'n' || c == 'N')  return false;
        else{
            std::cout << "Errore nell'inserimento input: riprovare con 'y' per procedere o 'n' per bloccare la transazione" <<"\n";
        }
    }
}

//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

void HumanPlayer::buy_land(int cost){   if (ask_input(cost))    Player::buy_land(cost);}
void HumanPlayer::buy_house(int cost){  if (ask_input(cost))    Player::buy_land(cost);}
void HumanPlayer::buy_hotel(int cost){  if (ask_input(cost))    Player::buy_hotel(cost);}
