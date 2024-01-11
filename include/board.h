#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <chrono>
#include <thread>
#include <vector>

class Player;

class Board{
    const int SIDE = 8;

    int n_economy = 8;
    int n_standard = 10;
    int n_luxurious = 6;

    int players_number;
    int turn;
    int max_turn_number;
    int turn_count;

    const char house = '*';
    const char hotel = '^';

    std::ofstream output_file;
    std::string file_name;

    //costi e spese
    const int through_start = 20;

    const int economic_land = 6, standard_land = 10, luxurious_land = 20;
    const int economic_house = 3, standard_house = 5, luxurious_house = 10;
    const int economic_hotel = 3, standard_hotel = 5, luxurious_hotel = 10;
    const int lodging_Ehouse = 2, lodging_Shouse = 4, lodging_Lhouse = 7;
    const int lodging_Ehotel = 4, lodging_Shotel = 8, lodging_Lhotel = 14;

    //caselle del tabellone
    struct Box{ //lascio libero accesso perché può avvenire solo in board, essendo membro privato
        std::string on_box;
        int index;
    };

    std::vector<Box> board = std::vector<Box>((4 * SIDE) - 4);

    const std::string box_types[3] = {"E", "S", "L"};

    std::vector<Player*> players = std::vector<Player*>(players_number);

    // -- FUNZIONI PRIVATE --

    static bool compare(const std::string& s1, const std::string& s2); 

    int convert_pos(int* pos);

    void fill_board(); //prepara il tabellone, chiamata dal costruttore

    void show();

    public:

        Board(Player& p1, Player& p2, Player& p3, Player& p4);

        void set_output_file(std::string file);
        void set_total_turns(int n);
    
        int get_side();

        int start_increment(); //valore incremento in fiorini al passare dal via

        bool next(); //funzione del turno

        void eliminate(int player_index);

        void p_order(); //ordine di gioco

        void print_board(); 

        void show_options(); //funge da "menù" per possibili funzioni da chiamare tramite terminale durante il proprio turno

        int whose_property(int* coordinates); 

        enum rows {A, B, C, D, E, F, G, H, I, L, M, N, O, P, Q, R, S, T, U, V, Z};

};

//valutare la convenienza o meno
std::string to_string(Board::rows c);

#endif //BOARD_H
