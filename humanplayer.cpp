#include "humanplayer.h"

//   ---  FUNZIONI AUSILIARIE  ---

bool HumanPlayer::ask_input(int cost){

    //Non stampo su file perché è la diretta interazione con l'utente, che avviene da terminale
    //Verrà stampata su file soltanto la decisione presa
    std::cout << "Il budget attuale è di " << budget << " fiorini." <<"\n";
    std::cout << "Si vuole procedere all'acquisto per " << cost <<" fiorini? [y/n] ";
    char c;
    std::cin >> c;
    while (true){
        if (c == 'y' || c == 'Y' || c == 's' || c == 'S')   return true;
        else if (c == 'n' || c == 'N')  return false;
        else{
            std::cout << "Errore nell'inserimento input: riprovare con 'y' per procedere o 'n' per bloccare la transazione" <<"\n";
        }
    }
}

//   ---  OVERRIDE VIRTUAL FUNCTIONS  ---

Player::purchase HumanPlayer::buy_land(int cost){
    if (ask_input(cost))    return Player::buy_land(cost);

    return purchase::NOT_DONE;
}
Player::purchase HumanPlayer::buy_house(int cost){  
    if (ask_input(cost))    return Player::buy_house(cost);
    
    return purchase::NOT_DONE;
}
Player::purchase HumanPlayer::buy_hotel(int cost){  
    if (ask_input(cost))    return Player::buy_hotel(cost);

    return purchase::NOT_DONE;    
}
