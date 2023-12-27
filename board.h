#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <algorithm>
#include <random>

class Board{
    
    const int HEIGHT = 8;
    const int WIDTH = 8;
    const int players_number = 4;
    const int start_value = 20;

    std::vector<std::vector<std::string>> board = std::vector<std::vector<std::string>>(HEIGHT, std::vector<std::string>(WIDTH));
    std::vector<char> letters {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'L', 'L', 'L', 'L', 'L', 'L'};

    std::vector<Player> players = std::vector<Player>(players_number);

    bool compare_throws(std::string s1, std::string s2); 

    //verifica se la posizione corrente (del giocatore che ha effettuato un movimento) appartiene 
    //a qualcuno, e restituisce il numero del giocatore (in riferimento all'array di giocatori)
    //Se il numero corrisponde al giocatore, può procedere a comprare una casa (o albergo)
    //Se il numero corrisponde ad un altro giocatore, si prosegue con il pagamento del dazio
    //Se nessuno possiede il terreno (-1) si può procedere ad acquistarlo
    //Per le verifiche utilizzare std::find()
    public:

        Board(); 
        Board(Player p1, Player p2, Player p3, Player p4);
    
        int get_height();
        int get_width();
        int start_increment();

        std::vector<char> get_letters();
        void fill_board();

        void p_order();

        void print_board();

        int whose_property(int* coordinates); 

};

enum class columns {A = 0, B, C, D, E, F, G, H, I, L, M, N, O, P, Q, R, S, T, U, V, Z};

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
        case columns::I : return "I";
        case columns::L : return "L";
        case columns::M : return "M";
        case columns::N : return "N";
        case columns::O : return "O";
        case columns::P : return "P";
        case columns::Q : return "Q";
        case columns::R : return "R";
        case columns::S : return "S";
        case columns::T : return "T";
        case columns::U : return "U";
        case columns::V : return "V";
        case columns::Z : return "Z";
    }
};

// 

#endif //BOARD_H

/*
      1        2        3        4        5        6        7        8
A: |      | |      | |      | |      | |      | |      | |      | |      |
B: |      | |                                                     |      |
C: |      | |                                                     |      |
D: |      | |                                                     |      |
E: |      | |                                                     |      |
F: |      | |                                                     |      |
G: |      | |                                                     |      |
H: |      | |      | |      | |      | |      | |      | |      | |      |

*/