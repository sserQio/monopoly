#include "board.h"
#include "player.h"


//   ---  COSTRUTTORI  ---
Board::Board(Player p1, Player p2, Player p3, Player p4) 
    : file_name("output.txt"), turn (0), players_number(4), n_economy(8), n_standard(10), n_luxurious(6) {
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


//   ---  FUNZIONI AUSILIARIE e DI GIOCO---

//creazione casuale del tabellone
void Board::fill_board(){
    //valutare se fare manualmente perché non so se possiamo usarlo
    //auto rng = std::default_random_engine {};
    //std::shuffle(std::begin(letters), std::end(letters), rng); // si mescolano gli elementi del vettore letters (i gradi dei terreni)

    // riempimento della tabella
    for (int x = 0; x < WIDTH; x++){
        for (int y = 0; y < HEIGHT; y++){
            if ((x == 0 && y == 0) || (x == 7 && y==0) ||(x==7 && y==7) ||(x==0 && y==7)){continue;}
            if ((x>1 && x<7) && (y>1 && y<7)){continue;}
            else {
                //board[x][y].on_box = letters.back();
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

//gestione del turno di un giocatore: AGGIUNGERE OPZIONE "show()"
bool Board::next(){
    output_file.open(file_name);
    Player& player = players.at(turn);
    std::string name = player.get_name();

    if (players_number == 1){
        output_file << name << " ha vinto la partita" << "\n";
        std::cout << name << " ha vinto la partita" << "\n"; 

        return true; 
    }

    if (turn >= players_number)     turn = 0;
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
    board[player_pos[0]][player_pos[1]].on_box += std::to_string(turn) + '|';

    //verifico in che cella mi trovo e agisco di conseguenza
    player_pos = player.get_pos();
    output_file << name << " è arrivato nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]) << "\n";
    std::cout << name << " è arrivato nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]) << "\n";

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

        else if (i != turn && box.at(2) == house){
            if (box.at(1) == 'E' && player.pay(players.at(i), lodging_Ehouse) >= 0){
                output_file << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
            }
            else if (box.at(1) == 'S' && player.pay(players.at(i), lodging_Shouse) >= 0){
                output_file << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
            }
            else if (box.at(1) == 'L' && player.pay(players.at(i), lodging_Lhouse) >= 0){
                output_file << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i).get_name() << "per il pernottamento in casa" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }

        else if (i != turn && box.at(2) == hotel){
            if (box.at(1) == 'E' && player.pay(players.at(i), lodging_Ehotel) >= 0){
                output_file << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
            }
            else if (box.at(1) == 'S' && player.pay(players.at(i), lodging_Shotel) >= 0){
                output_file << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
            }
            else if (box.at(1) == 'L' && player.pay(players.at(i), lodging_Lhotel) >= 0){
                output_file << name << " paga " << lodging_Lhotel << " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Lhotel<< " fiorini a " << players.at(i).get_name() << "per il pernottamento in hotel" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }
    }

    output_file << name << " termina il turno" << "\n";
    std::cout << name << " termina il turno" << "\n" << "\n";
    output_file.close();
    turn++;

    return false;
}

void Board::eliminate(int player_index){
    int* player_pos = players.at(player_index).get_pos();

    //elimino il giocatore dal tabellone nella sua posizione corrente
    int i = board[player_pos[0]][player_pos[1]].on_box.find(std::to_string(player_index));
    board[player_pos[0]][player_pos[1]].on_box.at(i) = '\0';

    //elimino tutte le proprietà del giocatore
    for (int j = 0; j < HEIGHT; j++){
        for(auto& i : board.at(j)){
            if (i.index == player_index){
                if (i.on_box.at(2) == '*' || i.on_box.at(2) == '^')     i.on_box.at(2) = '\0';
                i.index = -1;
            }
        }
    }
    players.erase(players.begin() + player_index);
    players_number--;

}

//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}

//   ---  HELPER FUNCTIONS  ---

std::string to_string(Board::rows c){
    /*switch(c){
        case Board::rows::A : return "A";
        case Board::rows::B : return "B";
        case Board::rows::C : return "C";
        case Board::rows::D : return "D";
        case Board::rows::E : return "E";
        case Board::rows::F : return "F";
        case Board::rows::G : return "G";
        case Board::rows::H : return "H";
        case Board::rows::I : return "I";
        case Board::rows::L : return "L";
        case Board::rows::M : return "M";
        case Board::rows::N : return "N";
        case Board::rows::O : return "O";
        case Board::rows::P : return "P";
        case Board::rows::Q : return "Q";
        case Board::rows::R : return "R";
        case Board::rows::S : return "S";
        case Board::rows::T : return "T";
        case Board::rows::U : return "U";
        case Board::rows::V : return "V";
        case Board::rows::Z : return "Z";
    }*/
}

