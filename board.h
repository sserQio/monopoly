#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <algorithm>
#include <random>
class Player;

class Board{
    
    const int HEIGHT = 8;
    const int WIDTH = 8;
    const int players_number = 4;
    int turn;

    //costi e spese
    const int through_start = 20;

    const int economic_land = 6, standard_land = 10, luxurious_land = 20;
    const int economic_house = 3, standard_house = 5, luxurious_house = 10;
    const int economic_hotel = 3, standard_hotel = 5, luxurious_hotel = 10;
    const int lodging_Ehouse = 2, lodgingShouse = 4, lodging_Lhouse = 7;
    const int lodging_Ehotel = 4, lodgingShotel = 8, lodgingLhotel = 14;

    std::ofstream output_file;
    std::string file_name;


    std::vector<std::vector<std::string> > board = std::vector<std::vector<std::string> >(HEIGHT, std::vector<std::string>(WIDTH));

    //modificare per supportare tabelloni di qualsiasi dimensioni.
    //std::vector<char> letters {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'L', 'L', 'L', 'L', 'L', 'L'};

    std::vector<Player> players = std::vector<Player>(players_number);

    static bool compare_throws(const std::string& s1, const std::string& s2); 

    //verifica se la posizione corrente (del giocatore che ha effettuato un movimento) appartiene 
    //a qualcuno, e restituisce il numero del giocatore (in riferimento all'array di giocatori)
    //Se il numero corrisponde al giocatore, può procedere a comprare una casa (o albergo)
    //Se il numero corrisponde ad un altro giocatore, si prosegue con il pagamento del dazio
    //Se nessuno possiede il terreno (-1) si può procedere ad acquistarlo
    //Per le verifiche utilizzare std::find()
    public:

        Board(); 
        Board(Player p1, Player p2, Player p3, Player p4);

        void set_output_file(std::string file_name);
    
        int get_height();
        int get_width();
        int start_increment();

        std::vector<char> get_letters();
        void fill_board();

        void next(); 

        void p_order();

        void print_board();

        int whose_property(int* coordinates); 

        enum class rows {A = 0, B, C, D, E, F, G, H, I, L, M, N, O, P, Q, R, S, T, U, V, Z};

};

//valutare la convenienza o meno


std::string to_string(Board::rows c);

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