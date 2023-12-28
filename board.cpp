#include "board.h"
#include "player.h"


//   ---  COSTRUTTORI  ---
Board::Board(Player p1, Player p2, Player p3, Player p4) : file_name("output.txt"), turn (0) {
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

/*
std::vector<char> Board::get_letters(){
    return letters;
}*/

//   ---  FUNZIONI AUSILIARIE e DI GIOCO---

//creazione casuale del tabellone
void Board::fill_board(){
    //valutare se fare manualmente perché non so se possiamo usarlo
    //auto rng = std::default_random_engine {};
    //std::shuffle(std::begin(letters), std::end(letters), rng); // si mescolano gli elementi del vettore letters (i gradi dei terreni)

    // riempimento della tabella
    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            if ((x==0 && y==0) || (x==7 && y==0) ||(x==7 && y==7) ||(x==0 && y==7)){continue;}
            if ((x>1 && x<7) && (y>1 && y<7)){continue;}
            else {
                //board[x][y] = letters.back();
                //letters.pop_back();
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

bool Board::compare_throws(const std::string& throw1, const std::string& throw2){
    return std::stoi(throw1.substr(1)) > std::stoi(throw2.substr(1));
}

int Board::whose_property(int* pos){
    return board[pos[0]][pos[1]].index;
}

void Board::next(){
    if (turn == players_number)     turn = 0;

    output_file.open(file_name);
    Player& player = players.at(turn);
    std::string name = player.get_name();
    output_file << "È il turno di " << name << "\n";
    std::cout << "È il turno di " << name << "\n";

    int n = player.throw_dice();
    output_file << name << "tira i dadi: " << n <<"\n";
    std::cout << name << "tira i dadi: " << n <<"\n";

    //rimuovo il player dalla sua posizione attuale nel tabellone
    int* player_pos = player.get_pos();
    for (int i = 0; i < board[player_pos[0]][player_pos[1]].on_box.length(); i++){
        if (board[player_pos[0]][player_pos[1]].on_box[i] == *std::to_string(turn).c_str()){
            board[player_pos[0]][player_pos[1]].on_box[i] = '\0';
        }
    }

    //controllo se sono passato per il via
    int prev_budget = player.get_budget();
    player.move(*this, n);
    if (player.get_budget() == prev_budget + through_start){
        output_file << name << " passa per il via e ritira" << through_start << "fiorini" <<"\n";
        std::cout << name << " passa per il via e ritira" << through_start << "fiorini" <<"\n";
    }

    //aggiungo il player nel tabellone
    n = board[player_pos[0]][player_pos[1]].on_box.length(); //riutilizzo n perché il valore del lancio non serve più
    board[player_pos[0]][player_pos[1]].on_box[n-1] = '\0';
    board[player_pos[0]][player_pos[1]].on_box += std::to_string(turn);

    //verifico in che cella mi trovo e agisco di conseguenza
    player_pos = player.get_pos();
    output_file << name << "si trova nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]) << "\n";
    std::cout << name << "si trova nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]) << "\n";

    if (!((player_pos[0] == 0 || player_pos[0] == HEIGHT-1) && (player_pos[1] == 0 || player_pos[1] == WIDTH-1))){
        //(se non sono in un angolo del tabellone)

        int i = whose_property(player_pos);
        std::string box = board[player_pos[0]][player_pos[1]].on_box;

        //Il terreno è libero
        if (i == -1){
            output_file << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";
            std::cout << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";

            if (box.at(1) == 'E' && player.buy_land(economic_land)){
                output_file << name << "compra il terreno per " << economic_land << "fiorini" <<"\n"; 
                std::cout << name << "compra il terreno per " << economic_land << "fiorini" <<"\n";

                board[player_pos[0]][player_pos[1]].index = turn;
            }
            else if (box.at(1) == 'S' && player.buy_land(standard_land)){
                output_file << name << "compra il terreno per " << standard_land << "fiorini" <<"\n"; 
                std::cout << name << "compra il terreno per " << standard_land << "fiorini" <<"\n";

                board[player_pos[0]][player_pos[1]].index = turn;
            }
            else if (box.at(1) == 'L' && player.buy_land(luxurious_land)){
                output_file << name << "compra il terreno per " << luxurious_land << "fiorini" <<"\n"; 
                std::cout << name << "compra il terreno per " << luxurious_land << "fiorini" <<"\n";

                board[player_pos[0]][player_pos[1]].index = turn;
            }
            else{
                output_file << name << "non ha fondi sufficienti per comprare il terreno " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per comprare il terreno " << "\n";
            }
        }

        //Il terreno è del giocatore, ma non possiede né case né hotel
        else if (i == turn && box.at(2) != hotel && box.at(2) != house){
            output_file << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";
            std::cout << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";

            if (box.at(1) == 'E' && player.buy_house(economic_house)){
                output_file << name << "compra una casa per " << economic_house << "fiorini" <<"\n"; 
                std::cout << name << "compra una casa per " << economic_house << "fiorini" <<"\n";

            }
            else if (box.at(1) == 'S' && player.buy_house(standard_house)){
                output_file << name << "compra una casa per " << standard_house << "fiorini" <<"\n"; 
                std::cout << name << "compra una casa per " << standard_house << "fiorini" <<"\n";
            }
            else if (box.at(1) == 'L' && player.buy_house(luxurious_house)){
                output_file << name << "compra una casa per " << luxurious_house << "fiorini" <<"\n"; 
                std::cout << name << "compra una casa per " << luxurious_house << "fiorini" <<"\n";

            }
            else{
                output_file << name << "non ha fondi sufficienti per investire in una casa " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per investire in una casa " << "\n";
            }
        }

        //Il terreno è del giocatore ed ha già una casa
        else if (i == turn && box.at(2) == house){
            output_file << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";
            std::cout << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";

            if (box.at(1) == 'E' && player.buy_hotel(economic_hotel)){
                output_file << name << "compra un hotel per " << economic_hotel << "fiorini" <<"\n"; 
                std::cout << name << "compra un hotel per " << economic_hotel << "fiorini" <<"\n";

            }
            else if (box.at(1) == 'S' && player.buy_hotel(standard_hotel)){
                output_file << name << "compra un hotel per " << standard_hotel << "fiorini" <<"\n"; 
                std::cout << name << "compra un hotel per " << standard_hotel << "fiorini" <<"\n";
            }
            else if (box.at(1) == 'L' && player.buy_hotel(luxurious_hotel)){
                output_file << name << "compra un hotel per " << luxurious_hotel << "fiorini" <<"\n"; 
                std::cout << name << "compra un hotel per " << luxurious_hotel << "fiorini" <<"\n";

            }
            else{
                output_file << name << "non ha fondi sufficienti per investire in un hotel " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per investire in un hotel " << "\n";
            }
        }

        else{ //in tutti gli altri casi index rappresenta uno degli altri giocatori

            //completare
        }
    }



}

//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}

//   ---  HELPER FUNCTIONS  ---

std::string to_string(Board::rows c){
    /*switch(c){
        case Board::columns::A : return "A";
        case Board::columns::B : return "B";
        case Board::columns::C : return "C";
        case Board::columns::D : return "D";
        case Board::columns::E : return "E";
        case Board::columns::F : return "F";
        case Board::columns::G : return "G";
        case Board::columns::H : return "H";
        case Board::columns::I : return "I";
        case Board::columns::L : return "L";
        case Board::columns::M : return "M";
        case Board::columns::N : return "N";
        case Board::columns::O : return "O";
        case Board::columns::P : return "P";
        case Board::columns::Q : return "Q";
        case Board::columns::R : return "R";
        case Board::columns::S : return "S";
        case Board::columns::T : return "T";
        case Board::columns::U : return "U";
        case Board::columns::V : return "V";
        case Board::columns::Z : return "Z";
    }*/
}

