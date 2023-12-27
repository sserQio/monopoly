#include "board.h"
#include "player.h"

//   ---  COSTRUTTORI  ---
Board::Board(Player p1, Player p2, Player p3, Player p4){
    players.at(0) = p1;
    players.at(1) = p2;
    players.at(2) = p3;
    players.at(3) = p4;
    fill_board();
}

//   ---  FUNZIONI DI ACCESSO  ---

int Board::get_height(){    return HEIGHT;}
int Board::get_width(){     return WIDTH;}
int Board::start_increment(){   return start_value;}


std::vector<char> Board::get_letters(){
    return letters;
}

//   ---  FUNZIONI AUSILIARIE  ---

//creazione casuale del tabellone
void Board::fill_board(){
    
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(letters), std::end(letters), rng); // si mescolano gli elementi del vettore letters (i gradi dei terreni)

    // riempimento della tabella
    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            if ((x==0 && y==0) || (x==7 && y==0) ||(x==7 && y==7) ||(x==0 && y==7)){continue;}
            if ((x>1 && x<7) && (y>1 && y<7)){continue;}
            else {
                board[x][y] = letters.back();
                letters.pop_back();
            }
        }
    }
}

/*creazione dell'ordine di lancio dei dadi tra i quattro giocatori
void Board::p_order(){
    int d1 = p1.throw_dice();
    int d2 = p2.throw_dice();
    int d3 = p3.throw_dice();
    int d4 = p4.throw_dice();
    std::vector<int> d = {p1.throw_dice(), p2.throw_dice(), p3.throw_dice(), p4.throw_dice()};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (d[i] == d[j] && i != j)
            {
                
            }
        }
    }
    std::sort(d.begin(), d.end());
    
}*/


//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}

