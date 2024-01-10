#include "../src/board.cpp"
#include "../src/cpuplayer.cpp"
#include "../src/humanplayer.cpp"
#include "../src/player.cpp"

int main(int argc, char* argv[]){
    std::string type;
    if (argc >= 2)  type = argv[1];

    Player* p1;
    int count;
    int number_of_turns;

    if (type != "computer" && type != "Computer" && type!= "human" && type != "Human"){

        std::cout << "Errore nell'acquisizione di input via riga di comando. Procedo via input da terminale: \n";
        std::cout << "Si vuole procedere con una partita di soli giocatori CPU o con un player umano? ['computer'/'human']: ";
        std::cin >> type;
        std::cin.ignore(1, '\n'); 
    }
    if (type == "computer" || type == "Computer"){

        p1 = new CPUPlayer();
    }
    else if (type == "human" || type == "Human"){

        std::cout << "Se si vuole, inserire il nome per il proprio giocatore, altrimenti continuare [ENTER]: ";

        std::getline(std::cin, type);

        p1 = new HumanPlayer();         
        if (type.length() != 0)   p1 -> set_name(type);
    }
    else {
        std::cout << "Errore nell'acquistizione di input. Riprovare da riga di comando" << "\n";
        exit(0);
    }


    std::cout << "Inserire numero massimo di round, o continuare [ENTER] per un assegnazione automatica: ";
    //riciclo type
    std::getline(std::cin, type);

    if (type.length() == 0)   number_of_turns = 10;
    else if (std::stoi(type) > 0)   number_of_turns = std::stoi(type);
    else{
        std::cout << "Valore non valido, procedo in automatico (10 turni)" << "\n";
        number_of_turns = 10;
    }
    CPUPlayer p2;
    CPUPlayer p3;
    CPUPlayer p4;

    Board board(*p1, p2, p3, p4);
    board.set_total_turns(number_of_turns);

    std::cout << "Inserire nome file di log degli eventi, oppure continuare [ENTER] per crearne uno in automatico: ";
    std::getline(std::cin, type);

    if (type.length() != 0)   board.set_output_file(type);

    std::cout << "\n";
    bool done = false;
    while (!done){
        if ( (done = board.next()) )    break;
        std::cout << "Continuare [ENTER] ";
        std::getline(std::cin, type);
    }
    return 0;
}