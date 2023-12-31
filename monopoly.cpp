#include "board.cpp"
#include "cpuplayer.cpp"
#include "humanplayer.cpp"

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
    }
    if (type == "computer" || type == "Computer"){

        std::cout << "Inserire numero massimo di round, o continuare [ENTER] per un assegnazione automatica: ";
        //riciclo type
        std::cin.ignore(1, '\n');
        std::getline(std::cin, type);
        if (type == "\n")   number_of_turns = 10;
        else if (std::stoi(type) > 0)   number_of_turns = std::stoi(type);
        else{
            std::cout << "Valore non valido, procedo in automatico (10 turni)" << "\n";
            number_of_turns = 10;
        }
        p1 = new CPUPlayer();
    }
    else if (type == "human" || type == "Human"){

        std::cout << "Se si vuole, inserire il nome per il proprio giocatore, altrimenti continuare [ENTER]: ";
        std::cin >> type;
        std::cout << "\n";
        p1 = new HumanPlayer();         
        if (type != "\n")   p1 -> set_name(type);
    }
    else {
        std::cout << "Errore nell'acquistizione di input. Riprovare da riga di comando" << "\n";
        exit(1);
    }

    CPUPlayer p2;
    CPUPlayer p3;
    CPUPlayer p4;

    Board board(*p1, p2, p3, p4);

    std::cout << "Inserire nome file di log degli eventi, oppure continuare [ENTER] per crearne uno in automatico: ";
    std::cin.ignore(1, '\n');
    std::getline(std::cin, type);
    std::cout << "\n";
    if (type != "\n")   board.set_output_file(type);

    bool done = false;
    while (!done)   done = board.next();

    delete p1;
    return 0;
}