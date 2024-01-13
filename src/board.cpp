//Autore e matricola: Favretto Mattia, 2066594

#include "../include/board.h"
#include "../include/player.h"
#include <algorithm>

//   ---  COSTRUTTORE  ---

Board::Board(Player& p1, Player& p2, Player& p3, Player& p4) 
    : file_name("output.txt"), turn(0), players_number(4), n_economy(8), n_standard(10), n_luxurious(6), max_turn_number(-1), turn_count(0) {
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

int Board::get_side(){    return SIDE;}

int Board::start_increment(){   return through_start;}


//   ---  FUNZIONI AUSILIARIE ---

//creazione casuale del tabellone
void Board::fill_board(){
    srand(time(0));
    // riempimento della tabella
    for (int x = 0; x < board.size(); x++){

        //imposto la partenza
        if (x == 0){  
            board[x].on_box = "| P |"; 
        }
        //imposto gli angoli (che non sono la partenza)
        else if (x % (SIDE - 1) == 0){
            board[x].on_box = "|   |"; 
        }
        //imposto (pseudo-)randomicamente le caselle nelle varie tipologie
        else {
            int t = rand()%3;
            if (t == 0 && n_economy > 0){
                board[x].on_box = "| " + box_types[t] + " |"; 
                n_economy--;
            }
            else if (t == 1 && n_standard > 0){
                board[x].on_box = "| " + box_types[t] + " |";
                n_standard--;
            }
            else if (t == 2 && n_luxurious > 0){
                board[x].on_box = "| " + box_types[t] + " |";
                n_luxurious--;
            }
            else{
                x--;
            }
        }
        //inizializzo l'indice di appartenenza del terreno al valore standard
        board[x].index = -1;
    }
}

//Funzione di confronto utilizzata da sort() in p_order e next()
bool Board::compare(const std::string& throw1, const std::string& throw2){
    return std::stoi(throw1.substr(1)) > std::stoi(throw2.substr(1));
}

//converte coordinate (y,x) in una posizione valida (e corrispondente) nel vettore board
int Board::convert_pos(int* pos){
    if (pos[1] >= pos[0])   return pos[0]+pos[1];
    //altrimenti
    return ((2*SIDE) - 2) + (SIDE - pos[1] - 1) + (SIDE - pos[0] - 1);
}

int Board::whose_property(int* pos){
    return board.at(convert_pos(pos)).index;
}

//stampa a terminale del tabellone corrente
void Board::print_board(){
    std::cout << "\n";
    std::string spaces = "";
    std::string standard_space = " "; // lo spazio per l'eventuale presenza di una casa o albergo
    std::string standard_box = "     ";

    //devo prevedere l'eventuale presenza di tutti i giocatori, così che la casella non vada a sovrapporsi
    //con la successiva a causa di un distanziamento troppo piccolo
    for(int i = 0; i < players_number; i++){
        standard_space+=" ";
    }

    for (int i = 2; i < SIDE; i++){
        spaces += standard_box + standard_space; //l'ampiezza necessaria per una casella standard "| E |" e il distanziamento dalla successiva
    }
    
    //stampo la prima riga con le coordinate delle colonne
    std::cout << standard_box;
    for (int i = 1; i <= SIDE; i++){
        std::cout<< i << "    " + standard_space; //così che sia sempre sopra il "tipo di casella"
    }
    std::cout << "\n";
    std::cout << "\n";

    for (int y = 0; y < SIDE; y++){
        std::cout << to_string(rows(y)) << "  ";

        for (int x = 0; x < SIDE; x++){

            std::string space = standard_space;
            int pos[2] = {y, x};
            int i = board.at(convert_pos(pos)).on_box.length();
            if (i > standard_space.length()){
                
                //sistemo il distanziamento a seconda della grandezza della casella e del numero di giocatori 
                std::string space2 (standard_space.length() - (i - standard_space.length() - (standard_box.length() - players_number -1)), ' ');
                space = space2;
            }

            std::cout << board.at(convert_pos(pos)).on_box << space;
            if (y > 0 && y < SIDE-1){
                pos[0] = y;
                pos[1] =SIDE - 1;
                std::cout << spaces << board.at(convert_pos(pos)).on_box;
                x = SIDE-1;
            }
        }
        std::cout << "\n";
        std::cout << "\n";
    }
    std::cout<< "\n";
}

//Se il giocatore è predisposto all'interazione via terminale (ad esempio HumanPlayer), gli si propone
//come interagire: al momento è presente la sola opzione show come da consegna, ma l'idea è che sia eventualmente
//ampliabile
void Board::show_options(){

    std::string input;
    std::cout << "Si digiti 'show' per visualizzare la situazione attuale della partita, o [ENTER] per continuare: ";
    
    std::getline(std::cin, input);

    if (input == "show" || input == "'show'")   show();
    //se digita altri caratteri termina automaticamente, non servono ulteriori else
}

//L'interazione con il giocatore avviene solo via terminale, sul log file compariranno solo le azioni intraprese
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

        std::cout << "\n";
    }

    //stampo i fiorini di ciascun giocatore
    std::cout << "\n" << "La situazione economica di ciascun giocatore è la seguente: " << "\n";
    for (auto i : players){
        std::cout << "\t" << i->get_name() <<" ha " << i->get_budget() << " fiorini" << "\n";
    }
    std::cout << "\n";
}

//   ---  FUNZIONI DI GIOCO  ---

//stabilisce l'ordine di gioco tra i giocatori
void Board::p_order(){

    //Scegliamo di non sovrascrivere il file di log ad ogni esecuzione e predisporlo invece
    //al supporto di più partite separate dall'identificazione di quando sono avvenute (data e ora locale)
    output_file.open(file_name, std::fstream::app|std::fstream::out);
    time_t now;
    time(&now);
    tm* date = localtime(&now);
    output_file << "\n" << "\t" << "--- NUOVA PARTITA --- " << asctime(date) << "\n";

    output_file << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";
    std::cout << "Si tirano i dadi per stabilire l'ordine di gioco" << "\n";

    std::vector<std::string> dice_throws (players_number);
    std::vector<Player*> temp = players;

    srand(time(0));
    //popolo il vettore dei lanci per poi ordinarlo in ordine decrescente
    for (int i = 0; i < players_number; i++){

        std::string n = std::to_string((*players.at(i)).throw_dice());
        output_file << players.at(i)->get_name() << " tira i dadi: " << n <<"\n";
        std::cout << players.at(i)->get_name() << " tira i dadi: " << n <<"\n";

        //uso stringhe per poter etichettare a ciascun lancio l'indice del giocatore che lo effettua
        dice_throws.at(i) = std::to_string(i) + n; 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::sort(dice_throws.begin(), dice_throws.end(), compare);
    
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

                int d = c;
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
                std::sort(dice_throws.begin()+d, dice_throws.begin()+c+1, compare);

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
    //Manca l'ultimo giocatore: lo inserisco in ultima posizione
    players.at(players_number-1) = temp.at(std::stoi(dice_throws.at(players_number-1).substr(0,1)));

    //stampo l'ordine di gioco
    output_file << "\n" <<"Si gioca nell'ordine: ";
    std::cout << "\n" <<"Si gioca nell'ordine: ";

    output_file << players.at(0)->get_name();
    std::cout << players.at(0)->get_name();

    for (int i = 1; i < players_number; i++){
        output_file << ", " << players.at(i) -> get_name();
        std::cout << ", " << players.at(i) -> get_name();
    }
                                                                                                      
    output_file << "\n" << "\n";
    std::cout << "\n" << "\n";
    output_file.close();
}

//Funzione che gestisce il turno di gioco: 
//  restituisce True solo se il turno comporta la fine della partita
bool Board::next(){
    //Se è la prima giocata, devo stabilire l'ordine di gioco
    if (turn_count == 0){
        p_order();

        //inserisco i giocatori nella casella di partenza
        for (int i = 0; i < players_number; i++){

            int* player_pos = players[i] -> get_pos();
            int n = board.at(convert_pos(player_pos)).on_box.length(); 
            //elimino i caratteri " |"
            board.at(convert_pos(player_pos)).on_box = board.at(convert_pos(player_pos)).on_box.substr(0, n-2);
            board.at(convert_pos(player_pos)).on_box += std::to_string(i+1) + " |";
        }
    }

    if (turn >= players_number)     turn = 0;

    Player& player = *players.at(turn);
    std::string name = player.get_name();
    std::string player_index = name.substr(name.length() - 2, 1); //il numero che appare tra le parentesi

    output_file.open(file_name, std::fstream::app|std::fstream::out);

    if (players_number == 1){
        output_file << name << " ha vinto la partita" << "\n";
        std::cout << name << " ha vinto la partita" << "\n"; 

        output_file.close();
        return true; 
    }

    if (max_turn_number == turn_count){

        std::vector<std::string> budgets(players_number); 

        for (int i = 0; i < players_number; i++){
            std::string n = std::to_string(i) + std::to_string((*players.at(i)).get_budget());
            budgets.at(i) = n;
        }
        //piuttosto che creare una compare apposita (che risparmierebbe il passaggio in stringhe), per non appesantire
        //il codice utilizzo la stessa sfruttata per p_order
        std::sort(budgets.begin(), budgets.end(), compare);

        std::cout << "Raggiunto il limite di turni. ";
        output_file << "Raggiunto il limite di turni. ";

        std::string budget = budgets.at(0).substr(1);
        if (budget != budgets.at(1).substr(1)){
            std::cout << "Vince, con " << budget << " fiorini: " << players.at(std::stoi(budgets.at(0).substr(0,1))) -> get_name() << "\n";
            output_file << "Vince, con " << budget << " fiorini: " << players.at(std::stoi(budgets.at(0).substr(0,1))) -> get_name() << "\n";
        }
        else{
            std::cout << "Vincono a parimerito, con " << budget << " fiorini:" << "\n";
            output_file << "Vincono a parimerito con " << budget << " fiorini:" << "\n";

            int i = 0;
            while (i < players_number && budgets.at(i).substr(1) == budget){
                output_file << "\t" << players.at(std::stoi(budgets.at(i).substr(0,1)))->get_name() << "\n";
                std::cout << "\t" <<  players.at(std::stoi(budgets.at(i).substr(0,1)))->get_name() << "\n";
                i++;
            }
        }
        output_file.close();
        return true;
    }

    output_file << "È il turno di " << name << "\n";
    std::cout << "È il turno di " << name << "\n";

    //Se è un giocatore con cui avere interazioni, gli offro la possibilità di scegliere cosa fare
    //prima di continuare il turno (nel nostro caso sarà solo show(), ma si possono aggiungere funzioni)
    bool interaction = player.interactions();
    if (interaction)    show_options();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    int n = player.throw_dice();
    output_file << name << " tira i dadi: " << n <<"\n";
    std::cout << name << " tira i dadi: " << n <<"\n";

    //rimuovo il player dalla sua posizione attuale nel tabellone
    int* player_pos = player.get_pos();
    int actual_pos = convert_pos(player_pos);

    for (int i = 2; i < board.at(actual_pos).on_box.length(); i++){ //Sarà sempre almeno dalla posizione 2 per: "| "
        if (board.at(actual_pos).on_box[i] == *player_index.c_str()){

            std::string::iterator j = board.at(actual_pos).on_box.begin() + i;
            board.at(actual_pos).on_box.erase(j, j+1);

            //se rimuovo da un angolo, per mantenere la lunghezza corretta devo aggiungere uno spazio 
            if (board.at(actual_pos).on_box[2] == ' '){
                board.at(actual_pos).on_box.insert(2, " ");
            }
        }
    }

    //controllo se sono passato per il via
    int prev_budget = player.get_budget();
    player.move(*this, n);

    if (player.get_budget() == prev_budget + through_start){

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        output_file << name << " passa per il via e ritira " << through_start << " fiorini" <<"\n";
        std::cout << name << " passa per il via e ritira " << through_start << " fiorini" <<"\n";
    }
    //Alla prima mossa, silenziosamente i giocatori acquisicono 20 fiorini (per come è strutturata la move)
    //quindi li rimuovo

    actual_pos = convert_pos(player.get_pos());

    //aggiungo il player nel tabellone

    n = board.at(actual_pos).on_box.length(); //riutilizzo n perché il valore del lancio non serve più
    //elimino i caratteri " |"
    board.at(actual_pos).on_box = board.at(actual_pos).on_box.substr(0, n-2);
    //se è un angolo vuoto   
    if (board.at(actual_pos).on_box[2] == ' ')   board.at(actual_pos).on_box.erase(board.at(actual_pos).on_box.end()-1);
    board.at(actual_pos).on_box += player_index + " |";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //verifico in che cella mi trovo e agisco di conseguenza
    player_pos = player.get_pos();
    output_file << name << " è arrivato nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]+1) << "\n";
    std::cout << name << " è arrivato nella casella " << to_string(rows(player_pos[0])) + std::to_string(player_pos[1]+1) << "\n";

    if (!((player_pos[0] == 0 || player_pos[0] == SIDE-1) && (player_pos[1] == 0 || player_pos[1] == SIDE-1))){
        //(se non sono in un angolo del tabellone)

        int i = whose_property(player_pos);
        std::string box = board.at(actual_pos).on_box;

        Player::purchase done = Player::purchase::NOT_DONE;
        //Il terreno è libero

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (i == -1){
            output_file << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";
            std::cout << "Il terreno è libero, procedo con verifiche per l'eventuale acquisto" << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(2) == 'E'){
            
                done = player.buy_land(economic_land);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra il terreno per " << economic_land << " fiorini" <<"\n"; 
                    std::cout << name << " compra il terreno per " << economic_land << " fiorini" <<"\n";

                    board.at(actual_pos).index = turn;
                }
            }
            else if (box.at(2) == 'S'){

                done = player.buy_land(standard_land);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra il terreno per " << standard_land << " fiorini" <<"\n"; 
                    std::cout << name << " compra il terreno per " << standard_land << " fiorini" <<"\n";

                    board.at(actual_pos).index = turn;
                }
            }
            else if (box.at(2) == 'L'){

                done = player.buy_land(luxurious_land);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra il terreno per " << luxurious_land << " fiorini" <<"\n"; 
                    std::cout << name << " compra il terreno per " << luxurious_land << " fiorini" <<"\n";

                    board.at(actual_pos).index = turn;
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non ha fondi sufficienti per comprare il terreno " << "\n"; 
                std::cout << name << " non ha fondi sufficienti per comprare il terreno " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non compra il terreno " << "\n"; 
                std::cout << name << " non compra il terreno " << "\n";
            }
        }

        //Il terreno è del giocatore, ma non possiede né case né hotel
        else if (i == turn && box.at(3) != hotel && box.at(3) != house){
            output_file << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";
            std::cout << name << " possiede il terreno, procedo con verifiche per l'eventuale acquisto di una casa " << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(2) == 'E'){

                done = player.buy_house(economic_house);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra una casa per " << economic_house << " fiorini" <<"\n"; 
                    std::cout << name << " compra una casa per " << economic_house << " fiorini" <<"\n";

                    //inserisco la casa nel tabellone
                    board.at(actual_pos).on_box.insert(3, "*");
                }
            }
            else if (box.at(2) == 'S'){

                done = player.buy_house(standard_house);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra una casa per " << standard_house << " fiorini" <<"\n"; 
                    std::cout << name << " compra una casa per " << standard_house << " fiorini" <<"\n";

                    //inserisco la casa nel tabellone
                    board.at(actual_pos).on_box.insert(3, "*");
                }
            }
            else if (box.at(2) == 'L'){

                done = player.buy_house(luxurious_house);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra una casa per " << luxurious_house << " fiorini" <<"\n"; 
                    std::cout << name << " compra una casa per " << luxurious_house << " fiorini" <<"\n";

                    //inserisco la casa nel tabellone
                    board.at(actual_pos).on_box.insert(3, "*");  
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non ha fondi sufficienti per investire in una casa " << "\n"; 
                std::cout << name << " non ha fondi sufficienti per investire in una casa " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non investe in una casa " << "\n"; 
                std::cout << name << " non investe in una casa " << "\n";
            }
        }

        //Il terreno è del giocatore ed ha già una casa
        else if (i == turn && box.at(3) == house){
            output_file << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";
            std::cout << name << " possiede una casa sul terreno, procedo con verifiche per l'eventuale upgrade a hotel" << "\n";

            //ripropongo il menù
            if (interaction)    show_options();

            if (box.at(2) == 'E'){

                done = player.buy_hotel(economic_hotel);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra un hotel per " << economic_hotel << " fiorini" <<"\n"; 
                    std::cout << name << " compra un hotel per " << economic_hotel << " fiorini" <<"\n";

                    //sostituisco la casa con l'albergo nel tabellone
                    board.at(actual_pos).on_box.at(3) = '^';
                }
            }
            else if (box.at(2) == 'S'){

                done = player.buy_hotel(standard_hotel);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra un hotel per " << standard_hotel << " fiorini" <<"\n"; 
                    std::cout << name << " compra un hotel per " << standard_hotel << " fiorini" <<"\n";

                    //sostituisco la casa con l'albergo nel tabellone
                    board.at(actual_pos).on_box.at(3) = '^';
                }
            }
            else if (box.at(2) == 'L'){

                done = player.buy_hotel(luxurious_hotel);
                if (done == Player::purchase::DONE){

                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    output_file << name << " compra un hotel per " << luxurious_hotel << " fiorini" <<"\n"; 
                    std::cout << name << " compra un hotel per " << luxurious_hotel << " fiorini" <<"\n";

                    //sostituisco la casa con l'albergo nel tabellone
                    board.at(actual_pos).on_box.at(3) = '^';
                }
            }

            if (done == Player::purchase::OUT_OF_BALANCE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non ha fondi sufficienti per investire in un hotel " << "\n"; 
                std::cout << name << " non ha fondi sufficienti per investire in un hotel " << "\n";
            }
            else if (done == Player::purchase::NOT_DONE){

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                output_file << name << " non investe in un hotel " << "\n"; 
                std::cout << name << " non investe in un hotel " << "\n";
            }
        }

        else if (i != turn && box.at(3) == house){
            if (box.at(2) == 'E' && player.pay(*players.at(i), lodging_Ehouse) >= 0){
                output_file << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Ehouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
            }
            else if (box.at(2) == 'S' && player.pay(*players.at(i), lodging_Shouse) >= 0){
                output_file << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Shouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
            }
            else if (box.at(2) == 'L' && player.pay(*players.at(i), lodging_Lhouse) >= 0){
                output_file << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
                std::cout << name << " paga " << lodging_Lhouse << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in casa" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }

        else if (i != turn && box.at(3) == hotel){
            if (box.at(2) == 'E' && player.pay(*players.at(i), lodging_Ehotel) >= 0){
                output_file << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Ehotel << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
            }
            else if (box.at(2) == 'S' && player.pay(*players.at(i), lodging_Shotel) >= 0){
                output_file << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Shotel << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
            }
            else if (box.at(2) == 'L' && player.pay(*players.at(i), lodging_Lhotel) >= 0){
                output_file << name << " paga " << lodging_Lhotel << " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
                std::cout << name << " paga " << lodging_Lhotel<< " fiorini a " << players.at(i)->get_name() << " per il pernottamento in hotel" << "\n";
            }
            else{
                output_file << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                std::cout << name << " non ha fondi sufficienti per il pernottamento: eliminato" << "\n";
                eliminate(turn);
            }
        }
    }

    //ripropongo il menù (if/else necessari per il corretto utilizzo di cin.ignore dato che voglio permettere l'utilizzo di [ENTER])
    if (interaction && (board.at(actual_pos).index == -1 || board.at(actual_pos).index == turn) 
            && board.at(actual_pos).on_box.substr(2,1) != name.substr(name.length() - 2, 1) && board.at(actual_pos).on_box[2]!= 'P'){
        
        std::cin.ignore();
        show_options();
    }
    else if (interaction)   show_options();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    output_file << name << " termina il turno" << "\n" << "\n";
    std::cout << name << " termina il turno" << "\n" << "\n";
    turn++;
    turn_count++;

    output_file.close();

    return false;
}

void Board::eliminate(int player_index){
    int* player_pos = players.at(player_index)->get_pos();
    int actual_pos = convert_pos(player_pos);

    //elimino il giocatore dal tabellone nella sua posizione corrente
    std::string name = players.at(player_index) -> get_name();

    //cerco l'indice di gioco (quello tra parentesi nel nome, non del vettore di players)
    int i = board.at(actual_pos).on_box.find(name.substr(name.length() - 2, 1));
    board.at(actual_pos).on_box.erase(board.at(actual_pos).on_box.begin()+i, board.at(actual_pos).on_box.begin()+i+1);

    //elimino tutte le proprietà del giocatore
    for (auto& i : board){

        if (i.on_box.at(3) == '*' || i.on_box.at(3) == '^')     i.on_box.erase(i.on_box.begin()+3, i.on_box.begin()+4);
        i.index = -1;
    }   
    players.erase(players.begin() + player_index);
    players_number--;
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

    return "";
}

