#include "player.h"

//   ---  FUNZIONI DI GIOCO  ---

int Player::throw_dice(){
    //srand(time(0));
    return ((rand()%6)+1 + (rand()%6)+1);
}

void Player::move(Board& b, int n){

    while(pos[0] == 0 && pos[1] < b.get_width() -1 && n>0){
        n--;
        if (pos[1] == 0)    budget+=b.start_increment(); //sono passato per il via
        pos[1]+=1;
    }
    while(pos[1] == b.get_width() -1 && pos[0] < b.get_height() -1 && n>0){ 
        n--;
        pos[0]+=1;
    }
    while(pos[0] == b.get_height() -1 && pos[1] > 0 && n>0){
        n--;
        pos[1]-=1;
    }
    while(pos[1] == 0 && pos[0] > 0 && n>0){
        n--;
        pos[0]-=1;
        if (pos[0] == 0)    budget+=b.start_increment();  //sono passato per il via
    }

    if(n > 0)   move(b, n);
}

Player::purchase Player::buy_land(int c){ 
    if (budget < c)     return purchase::OUT_OF_BALANCE;
    //altrimenti
    budget -= c;

    lands.push_back(to_string(Board::rows(pos[0])) += std::to_string(pos[1]+1).c_str());

    return purchase::DONE;
}

Player::purchase Player::buy_house(int c){ 
    if (budget < c)     return purchase::OUT_OF_BALANCE;

    budget -= c;
    
    std::string coordinates = to_string(Board::rows(pos[0])) += std::to_string(pos[1]+1).c_str();
    houses.push_back(coordinates);

    //elimino la posizione dalla lista di terreni posseduti (indicante i terreni senza costruzione)
    //effettuo un controllo sull'iteratore restituito perché voglio un'indipendenza dalle regole di gioco:
        //se definissi un diverso board in cui è possibile acquistare direttamente una casa, non dovrò
        //modificare il metodo
    std::vector<std::string>::iterator i = std::find(lands.begin(), lands.end(), coordinates);
    if (i != lands.end())   lands.erase (i); 
    
    return purchase::DONE;
}

Player::purchase Player::buy_hotel(int c){
    if (budget < c)     return purchase::OUT_OF_BALANCE;

    budget -= c;
    
    std::string coordinates = to_string(Board::rows(pos[0])) += std::to_string(pos[1]+1).c_str();
    hotels.push_back(coordinates);

    std::vector<std::string>::iterator i = std::find(houses.begin(), houses.end(), coordinates);
    if (i != houses.end())      houses.erase(i);

    return purchase::DONE;
}

int Player::pay(Player& p2, int c){
    //se il pagamento è negativo, lo interpreto come un guadagno, altrimenti avrei potuto lanciare un eccezione
    if (c < 0)  return p2.pay(*this, abs(c));

    //in caso il pagante non abbia sufficienti fondi, p2 riceve solo una parte del compenso
    if( c > budget)     p2.budget += budget; 
    else{   p2.budget += c;}

    //non lancio eccezioni in caso di saldo negativo perché lascio la gestione delle regole al tabellone
    return budget -= c;
}

//   ---  FUNZIONI DI ACCESSO  ---

std::string Player::get_name(){
    return name;
}

void Player::set_name(std::string word){
    name = word; 
}

void Player::set_budget(int n){
    if (n < 0)  throw Invalid_Budget();
    budget = n;
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

