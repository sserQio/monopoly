#ifndef BOARD_H
#define BOARD_H


class Board{

    const int HEIGHT = 8;
    const int WIDTH = 8;
    
    const int start_value = 20;

    std::vector<std::vector<std::string> > board; 

    //verifica se la posizione corrente (del giocatore che ha effettuato un movimento) appartiene 
    //a qualcuno, e restituisce il numero del giocatore (in riferimento all'array di giocatori)
    //Se il numero corrisponde al giocatore, può procedere a comprare una casa (o albergo)
    //Se il numero corrisponde ad un altro giocatore, si prosegue con il pagamento del dazio
    //Se nessuno possiede il terreno (-1) si può procedere ad acquistarlo
    //Per le verifiche utilizzare std::find()
    public: 
        Board(Player p1, Player p2, Player p3, Player p4);

        int get_height();
        int get_width();
        int start_increment();

        int whose_property(int* coordinates); 

};

enum class columns {A = 0, B, C, D, E, F, G, H};

std::string to_string(columns c){
    switch(c){
        case columns::A : return "A";
        case columns::B : return "B";
        case columns::C : return "C";
        case columns::D : return "D";
        case columns::E : return "E";
        case columns::F : return "F";
        case columns::G : return "G";
        case columns::H : return "H";
    }
};


#endif //BOARD_H