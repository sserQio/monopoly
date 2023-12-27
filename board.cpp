#include "board.h"
#include "player.h"


//   ---  COSTRUTTORI  ---
Board::Board(Player p1, Player p2, Player p3, Player p4) : file_name("output.txt") {
    players.at(0) = p1;
    players.at(1) = p2;
    players.at(2) = p3;
    players.at(3) = p4;
    fill_board();
}

//   ---  FUNZIONI DI ACCESSO  ---

void Board::set_output_file(std::string name){ 
    file_name = name;
}

int Board::get_height(){    return HEIGHT;}
int Board::get_width(){     return WIDTH;}
int Board::start_increment(){   return through_start;}


std::vector<char> Board::get_letters(){
    return letters;
}

//   ---  FUNZIONI AUSILIARIE  ---

//creazione casuale del tabellone
void Board::fill_board(){
    //valutare se fare manualmente perché non so se possiamo usarlo
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
    output_file.open(file_name, std::ios::out);
    output_file << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";
    std::cout << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";

    std::vector<std::string> dice_throws (players_number);
    for (int i = 0; i < players_number; i++){
        std::string n = std::to_string(players.at(i).throw_dice());
        output_file << players.at(i).get_name() << " tira i dadi: " << n <<"\n";
        std::cout << players.at(i).get_name() << " tira i dadi: " << n <<"\n";

        //uso stringhe per poter etichettare a ciascun lancio l'indice del giocatore
        dice_throws.at(i) = std::to_string(i) + n; 
    }
    std::sort(dice_throws.begin(), dice_throws.end(), compare_throws);
    
    //riordino il vector di giocatori nel modo corretto, stabilito dal lancio dei dadi
    for (int i = 0; i < players_number - 1; i++){
        if (dice_throws.at(i).substr(1) != dice_throws.at(i+1).substr(1)){ //i valori dei lanci dono diversi
            std::swap(players.at(i), players.at(std::stoi(dice_throws.at(i).substr(0,1))));
            //(il primo elemento di dice_throws contiene l'etichetta del giocatore che giocherà per primo)
            
            //Inserisco un elemento identificativo dell'ordine anche nel nome del giocatore
            players.at(i).set_name(players.at(i).get_name()+" ("+std::to_string(i+1)+"°)");
        }
        else{ //sono in una sezione della lista di lanci ove ho ottenuto valori uguali: devo rilanciare
            
            output_file << "In " << i+1 << "° posizione vi sono giocatori in parimerito." << "\n";
            output_file << "Si procede con il rilancio dei dadi per quest'ultimi" <<"\n";
            std::cout << "In " << i+1 << "° posizione vi sono giocatori in parimerito." << "\n";
            std::cout << "Si procede con il rilancio dei dadi per quest'ultimi" <<"\n";

            bool done = false;
            int c = i;
            while (!done){
                int value = std::stoi(dice_throws.at(c).substr(1));
    
                //ritiro i dadi finché sono in tale sezione della lista (di lanci uguali)
                std::string n = std::to_string(players.at(c).throw_dice());

                output_file << players.at(c).get_name() << "ritira: " << n << "\n";
                std::cout << players.at(c).get_name() << "ritira: " << n << "\n";
                
                dice_throws.at(c) = dice_throws.at(c)[0] + n;

                while(std::stoi(dice_throws.at(c++).substr(1)) == value){
                    std::string n = std::to_string(players.at(c).throw_dice());

                    output_file << players.at(c).get_name() << "ritira: " << n << "\n";
                    std::cout << players.at(c).get_name() << "ritira: " << n << "\n";

                    dice_throws.at(c) = dice_throws.at(c)[0] + n;
                }
                c--;
                //riordino quella porzione di lista secondo i nuovi lanci
                std::sort(dice_throws.begin()+i, dice_throws.end()-c, compare_throws);

                done = true; //assumiamo di aver finito

                //controllo se ci sono ancora lanci uguali ed eventualmente reitero
                for (int j = i; j < c; j++){
                    if (dice_throws.at(j).substr(1) == dice_throws.at(j+1).substr(1)){
                        output_file << "Vi sono ancora pareggi per la " << j+1 << "° posizione: reitero" <<"\n";
                        std::cout << "Vi sono ancora pareggi per la " << j+1 << "° posizione: reitero" <<"\n";

                        c = j; //la prossima iterazione dei nuovi lanci parte da j
                        done = false;
                        break;
                    }   
                }
            }
            i--;
        }   
        
    }
    //manca il nome aggiornato all'ultimo player
    players.at(players_number-1).set_name(players.at(players_number-1).get_name()+" ("+std::to_string((players_number-1))+"°)");

    //stampo l'ordine di gioco
    output_file << "\n" <<"Si gioca nell'ordine: ";
    std::cout << "\n" <<"Si gioca nell'ordine: ";
    output_file << players.at(0).get_name();
    std::cout << players.at(0).get_name();
    for (int i = 1; i < players_number; i++){
        output_file << ", " << players.at(i).get_name();
        std::cout << ", " << players.at(i).get_name();
    }
    output_file << "\n" << "\n";
    std::cout << "\n" << "\n";
    output_file.close();
}

bool Board::compare_throws(std::string throw1, std::string throw2){
    return std::stoi(throw1.substr(1)) > std::stoi(throw2.substr(1));
}

//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}

