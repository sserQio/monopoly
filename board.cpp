#include "board.h"
#include "player.cpp"

//   ---  COSTRUTTORI  ---
Board::Board(Player& p1, Player& p2, Player& p3, Player& p4) 
    : file_name("output.txt"), turn (0), players_number(4), n_economy(8), n_standard(10), n_luxurious(6), max_turn_number(-1), state(false) {
    players.at(0) = &p1;
    players.at(1) = &p2;
    players.at(2) = &p3;
    players.at(3) = &p4;
    //Oltre all'eventuale nome personalizzato, aggiungo un numero identificativo ai giocatori
    for(int i = 0; i < players_number; i++)     players.at(i)->set_name(players.at(i)->get_name() +" ("+ std::to_string(i+1) + ")");
    fill_board();
}

//   ---  FUNZIONI DI ACCESSO  ---

void Board::set_output_file(std::string name){ 
    file_name = name;
}

void Board::set_total_turns(int n){
    max_turn_number = n;
}

int Board::get_height(){    return HEIGHT;}
int Board::get_width(){     return WIDTH;}
int Board::start_increment(){   return through_start;}


//   ---  FUNZIONI AUSILIARIE ---

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

bool Board::compare_throws(const std::string& throw1, const std::string& throw2){
    return std::stoi(throw1.substr(1)) > std::stoi(throw2.substr(1));
}

int Board::whose_property(int* pos){
    return board[pos[0]][pos[1]].index;
}

//stampa a terminale del tabellone corrente
void Board::print_board(){
    
}

//   ---  FUNZIONI DI GIOCO  ---

//stabilisce l'ordine di gioco tra i giocatori
void Board::p_order(){
    output_file.open(file_name, std::ios::out);
    output_file << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";
    std::cout << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";

    std::vector<std::string> dice_throws (players_number);
    std::vector<Player*> temp = players;

    srand(time(0));
    for (int i = 0; i < players_number; i++){
        std::string n = std::to_string((*players.at(i)).throw_dice());
        output_file << players.at(i)->get_name() << " tira i dadi: " << n <<"\n";
        std::cout << players.at(i)->get_name() << " tira i dadi: " << n <<"\n";
        //uso stringhe per poter etichettare a ciascun lancio l'indice del giocatore
        dice_throws.at(i) = std::to_string(i) + n; 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::sort(dice_throws.begin(), dice_throws.end(), compare_throws);
    
    //riordino il vector di giocatori nel modo corretto, stabilito dal lancio dei dadi
    for (int i = 0; i < players_number - 1; i++){
        if (dice_throws.at(i).substr(1) != dice_throws.at(i+1).substr(1)){ //i valori dei lanci dono diversi

            players.at(i) = temp.at(std::stoi(dice_throws.at(i).substr(0,1)));
            //(il primo elemento di dice_throws contiene l'etichetta del giocatore che giocherà per primo)

        }
        else{ //sono in una sezione della lista di lanci ove ho ottenuto valori uguali: devo rilanciare
            
            output_file << "In " << i+1 << "° posizione vi sono giocatori in parimerito. Si procede con il rilancio dei dadi per quest'ultimi" << "\n";
            std::cout << "In " << i+1 << "° posizione vi sono giocatori in parimerito. Si procede con il rilancio dei dadi per quest'ultimi" << "\n";

            bool done = false;
            int c = i;
            while (!done){
                int value = std::stoi(dice_throws.at(c).substr(1));
    
                //ritiro i dadi finché sono in tale sezione della lista (di lanci uguali)
                std::string n = std::to_string(temp.at(std::stoi(dice_throws.at(c).substr(0,1)))->throw_dice());

                output_file << temp.at(std::stoi(dice_throws.at(c).substr(0,1)))->get_name() << " ritira: " << n << "\n";
                std::cout << temp.at(std::stoi(dice_throws.at(c).substr(0,1)))->get_name() << " ritira: " << n << "\n";
                dice_throws.at(c) = dice_throws.at(c)[0] + n;

                //per una migliore visualizzazione e funzionamento della pseudo-randomicità dei lanci
                //aspetto mezzo secondo prima di rilanciare
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                while(c < players_number-1 && std::stoi(dice_throws.at(c+1).substr(1)) == value){
                    c++;
                    int j = std::stoi(dice_throws.at(c).substr(0,1));
                    std::string n = std::to_string(temp.at(j)->throw_dice());

                    output_file << temp.at(j)->get_name() << " ritira: " << n << "\n";
                    std::cout << temp.at(j)->get_name() << " ritira: " << n << "\n";

                    dice_throws.at(c) = dice_throws.at(c)[0] + n;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                //riordino quella porzione di lista secondo i nuovi lanci
                std::sort(dice_throws.begin()+i, dice_throws.begin()+c+1, compare_throws);
                for (auto i : dice_throws)  std::cout << i << "\n";
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
            //inibisco il valore contenuto nel player nell'ultima posizione che conteneva un valore uguale
            //altrimenti rischio che il valore ottenuto rilanciando risulti uguale al valore ottenuto precedentemente dal giocatore successivo
            dice_throws.at(c)[1] = '0'; 
            //riparto dallo stesso giocatore da cui era partita la sezione di lanci uguali (così che venga propriamente inserito in players)
            i--;
        }
    }
    players.at(players_number-1) = temp.at(std::stoi(dice_throws.at(players_number-1).substr(0,1)));

    //stampo l'ordine di gioco, sistemando man mano l'array di giocatori
    output_file << "\n" <<"Si gioca nell'ordine: ";
    std::cout << "\n" <<"Si gioca nell'ordine: ";

    output_file << players.at(0)->get_name();
    std::cout << players.at(0)->get_name();

    for (int i = 1; i < players_number; i++){
        output_file << ", " << players.at(i)->get_name();
        std::cout << ", " << players.at(i)->get_name();
    }
    output_file << "\n" << "\n";
    std::cout << "\n" << "\n";
    output_file.close();
    state = true; //l'ordine è stabilito: la partita può iniziare
}

//gestione del turno di un giocatore: AGGIUNGERE OPZIONE "show()"
bool Board::next(){
    //Se è la prima giocata, devo stabilire l'ordine di gioco
    if (state == false){
        p_order();
    }

    output_file.open(file_name);
    Player& player = *players.at(turn);
    std::string name = player.get_name();

    if (players_number == 1){
        output_file << name << " ha vinto la partita" << "\n";
        std::cout << name << " ha vinto la partita" << "\n"; 

        return true; 
    }

    if (max_turn_number == 0){
        int budget = player.get_budget();
        for (int i = 0; i < players_number; i++){
            int n = players.at(i)->get_budget();
            if (n < budget){
                players.erase(players.begin()+i);
                players_number--;
            }
            else if (n > budget){
                player = *players.at(i); //il nuovo riferimento è il giocatore con il budget maggiore
                players.erase(players.begin() + turn);
                turn = i; //utile in caso si trovi un altro giocatore con budget maggiore
                players_number--;
                //se ci fossero giocatori precedentemente salvati in fondo al vettore perché con budget uguale, li rimuovo
                while (players.back()->get_budget() == budget){
                    players.pop_back();
                    players_number--;
                }
                budget = n;
            }
            else{ //sono uguali: mantengo entrambi i giocatori in lista perché vinceranno parimerito

                //salvo i giocatori con budget uguale in coda al vettore per un eventuale rimozione più semplice
                players.push_back(players.at(i)); 
                players.erase(players.begin() + i);
            }
        }
        if (players_number != 1){
            output_file << "Raggiunto il limite di turni. I vincitori, a parimerito con " << budget << " fiorini, sono: " << "\n";
            std::cout << "Raggiunto il limite di turni. I vincitori, a parimerito con " << budget << " fiorini, sono: " << "\n";
        }
        else{
            output_file << "Raggiunto il limite di turni. Il vincitore per maggior numero di fiorini (" << budget << ") è:";
            std::cout  << "Raggiunto il limite di turni. Il vincitore per maggior numero di fiorini (" << budget << ") è:";
        }
        for(auto i : players){
            output_file << "\t" << i->get_name() << "\n";
            std::cout << "\t" << i->get_name() << "\n";
        }
        return true;
    }
    if (turn >= players_number)     turn = 0;
    output_file << "È il turno di " << name << "\n";
    std::cout << "È il turno di " << name << "\n";

    //Se è un giocatore con cui avere interazioni, gli offro la possibilità di scegliere cosa fare
    //prima di continuare il turno (nel nostro caso sarà solo show(), ma si possono aggiungere funzioni)
    bool interaction = player.interactions();
    if (interaction)    show_options();

    int n = player.throw_dice();
    output_file << name << " tira i dadi: " << n <<"\n";
    std::cout << name << " tira i dadi: " << n <<"\n";

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

        Player::purchase done = Player::purchase::NOT_DONE;
        //Il terreno è libero
        if (i == -1){
            output_file << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";
            std::cout << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(1) == 'E'){
            
                done = player.buy_land(economic_land);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra il terreno per " << economic_land << "fiorini" <<"\n"; 
                    std::cout << name << "compra il terreno per " << economic_land << "fiorini" <<"\n";

                    board[player_pos[0]][player_pos[1]].index = turn;
                }
            }
            else if (box.at(1) == 'S'){

                done = player.buy_land(standard_land);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra il terreno per " << standard_land << "fiorini" <<"\n"; 
                    std::cout << name << "compra il terreno per " << standard_land << "fiorini" <<"\n";

                    board[player_pos[0]][player_pos[1]].index = turn;
                }
            }
            else if (box.at(1) == 'L'){

                done = player.buy_land(luxurious_land);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra il terreno per " << luxurious_land << "fiorini" <<"\n"; 
                    std::cout << name << "compra il terreno per " << luxurious_land << "fiorini" <<"\n";

                    board[player_pos[0]][player_pos[1]].index = turn;
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){
                output_file << name << "non ha fondi sufficienti per comprare il terreno " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per comprare il terreno " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){
                output_file << name << "non compra il terreno " << "\n"; 
                std::cout << name << "non compra il terreno " << "\n";
            }
        }

        //Il terreno è del giocatore, ma non possiede né case né hotel
        else if (i == turn && box.at(2) != hotel && box.at(2) != house){
            output_file << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";
            std::cout << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(1) == 'E'){

                done = player.buy_house(economic_house);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra una casa per " << economic_house << "fiorini" <<"\n"; 
                    std::cout << name << "compra una casa per " << economic_house << "fiorini" <<"\n";
                }
            }
            else if (box.at(1) == 'S'){

                done = player.buy_house(standard_house);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra una casa per " << standard_house << "fiorini" <<"\n"; 
                    std::cout << name << "compra una casa per " << standard_house << "fiorini" <<"\n";
                }
            }
            else if (box.at(1) == 'L'){

                done = player.buy_house(luxurious_house);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra una casa per " << luxurious_house << "fiorini" <<"\n"; 
                    std::cout << name << "compra una casa per " << luxurious_house << "fiorini" <<"\n";
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){
                output_file << name << "non ha fondi sufficienti per investire in una casa " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per investire in una casa " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){
                output_file << name << "non investe in una casa " << "\n"; 
                std::cout << name << "non investe in una casa " << "\n";
            }
        }

        //Il terreno è del giocatore ed ha già una casa
        else if (i == turn && box.at(2) == house){
            output_file << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";
            std::cout << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(1) == 'E'){

                done = player.buy_hotel(economic_hotel);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra un hotel per " << economic_hotel << "fiorini" <<"\n"; 
                    std::cout << name << "compra un hotel per " << economic_hotel << "fiorini" <<"\n";
                }
            }
            else if (box.at(1) == 'S'){

                done = player.buy_hotel(standard_hotel);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra un hotel per " << standard_hotel << "fiorini" <<"\n"; 
                    std::cout << name << "compra un hotel per " << standard_hotel << "fiorini" <<"\n";
                }
            }
            else if (box.at(1) == 'L'){

                done = player.buy_hotel(luxurious_hotel);
                if (done == Player::purchase::DONE){
                    output_file << name << "compra un hotel per " << luxurious_hotel << "fiorini" <<"\n"; 
                    std::cout << name << "compra un hotel per " << luxurious_hotel << "fiorini" <<"\n";
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){
                output_file << name << "non ha fondi sufficienti per investire in un hotel " << "\n"; 
                std::cout << name << "non ha fondi sufficienti per investire in un hotel " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){
                output_file << name << "non investe in un hotel " << "\n"; 
                std::cout << name << "non investe in un hotel " << "\n";
            }
        }

        else if (i != turn && box.at(2) == house){
            if (box.at(1) == 'E' && player.pay(*players.at(i), lodging_Ehouse) >= 0){
                output_file << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
            }
            else if (box.at(1) == 'S' && player.pay(*players.at(i), lodging_Shouse) >= 0){
                output_file << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
            }
            else if (box.at(1) == 'L' && player.pay(*players.at(i), lodging_Lhouse) >= 0){
                output_file << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in casa" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }

        else if (i != turn && box.at(2) == hotel){
            if (box.at(1) == 'E' && player.pay(*players.at(i), lodging_Ehotel) >= 0){
                output_file << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
            }
            else if (box.at(1) == 'S' && player.pay(*players.at(i), lodging_Shotel) >= 0){
                output_file << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
            }
            else if (box.at(1) == 'L' && player.pay(*players.at(i), lodging_Lhotel) >= 0){
                output_file << name << " paga " << lodging_Lhotel << " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Lhotel<< " fiorini a " << players.at(i)->get_name() << "per il pernottamento in hotel" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }
    }

    //ripropongo il menù
    if (interaction)    show_options();

    output_file << name << " termina il turno" << "\n";
    std::cout << name << " termina il turno" << "\n" << "\n";
    output_file.close();
    turn++;
    if (max_turn_number != -1)  max_turn_number--;

    return false;
}

void Board::eliminate(int player_index){
    int* player_pos = players.at(player_index)->get_pos();

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

void Board::show_options(){
    std::string input;
    std::cout << "Si digiti 'show' per visualizzare la situazione attuale della partita, o ENTER per continuare: ";
    std::getline(std::cin, input);

    if (input == "show" || input == "'show'")   show();
    else if (input == "\n")    return;
    //se digita altri caratteri termina automaticamente, non servono ulteriori else
}

void Board::show(){
    std::cout << "\n" << "Ecco la situazione attuale della partita: " << "\n";
    print_board();

    //stampo le posizioni di alberghi, case e terreni vuoti di ciascun giocatore
    for (auto i : players){
        std::string name = i->get_name();

        std::cout << name <<" possiede:" << "\n";

        std::cout << "\t" << "Alberghi nelle posizioni: ";
        for (auto j : i->get_hotels())  std::cout << j << " ";

        std::cout << "\n" << "\t" << "Case nelle posizioni: ";
        for (auto j : i->get_houses())   std::cout << j << " ";

        std::cout << "\n" << "\t" << "Terreni vuoti nelle posizioni: ";
        for (auto j : i->get_lands())    std::cout << j << " ";
    }

    //stampo i fiorini di ciascun giocatore
    std::cout << "\n" << "La situazione economica di ciascun giocatore è la seguente: " << "\n";
    for (auto i : players){
        std::cout << "\t" << i->get_name() <<" ha " << i->get_budget() << "fiorini" << "\n";
    }
    std::cout << "\n";
}

//   ---  HELPER FUNCTIONS  ---

std::string to_string(Board::rows c){
    switch(c){
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
    }
}

