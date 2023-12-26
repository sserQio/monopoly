#include "board.h"
#include "player.h"

//   ---  COSTRUTTORI  ---
Board::Board(Player p1, Player p2, Player p3, Player p4) : p1(p1), p2(p2), p3(p3), p4(p4){
    fill_board();
}



int Board::get_height(){    return HEIGHT;}
int Board::get_width(){     return WIDTH;}

// funzione di accesso
std::vector<char> Board::get_letters(){
    return letters;
}

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

//creazione dell'ordine di lancio dei dadi tra i quattro giocatori
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
    
}


//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}




void Board::p_order(){
    int tp1 = p1.throw_dice();
    int tp2 = p2.throw_dice();
    int tp3 = p3.throw_dice();
    int tp4 = p4.throw_dice();
    std::vector<int> allt = {tp1, tp2, tp3, tp4};
    
}