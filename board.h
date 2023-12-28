#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <algorithm>
#include <random>
class Player;

class Board{
    
    const int HEIGHT = 8;
    const int WIDTH = 8;

    int players_number;
    int turn;

    const char house = '*';
    const char hotel = '^';

    //costi e spese
    const int through_start = 20;

    const int economic_land = 6, standard_land = 10, luxurious_land = 20;
    const int economic_house = 3, standard_house = 5, luxurious_house = 10;
    const int economic_hotel = 3, standard_hotel = 5, luxurious_hotel = 10;
    const int lodging_Ehouse = 2, lodging_Shouse = 4, lodging_Lhouse = 7;
    const int lodging_Ehotel = 4, lodging_Shotel = 8, lodging_Lhotel = 14;

    std::ofstream output_file;
    std::string file_name;

    struct Box{ //lascio libero accesso perché può avvenire solo in board, essendo membro privato
        std::string on_box;
        int index;
    };

    std::vector<std::vector<Box> > board = std::vector<std::vector<Box> >(HEIGHT, std::vector<Box>(WIDTH));

    //modificare per supportare tabelloni di qualsiasi dimensioni.
    //std::vector<char> letters {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'L', 'L', 'L', 'L', 'L', 'L'};

    std::vector<Player> players = std::vector<Player>(players_number);

    //lista di ciascuna casella con eventuale indice di proprietà di un giocatore.
    //Utile per migliorare notevolmente le prestazioni in caso di necessità di verificare a che appartenga un terreno. 
    //(diventano Θ(1))

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
        void eliminate(int player_index);

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