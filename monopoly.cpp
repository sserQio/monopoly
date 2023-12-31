#include "board.cpp"
#include "player.cpp"
#include "humanplayer.cpp"
#include "cpuplayer.cpp"

int main(int argc, char* argv[]){
    std::string type = argv[1];

    Player* p1;
    int count;
    int number_of_turns;

    if (type != "computer" && type != "Computer" && type!= "human" && type != "Human"){

        std::cout << "Errore nell'acquisizione di input via riga di comando. Procedo via input da terminale: \n";
        std::cout << "Si vuole procedere con una partita di soli giocatori CPU o con un player umano? ['computer'/'human']: ";
        std::cin >> type;
    }
    else if (type == "computer" || type == "Computer"){

        std::cout << "Inserire numero massimo di round, o continuare [ENTER] per un assegnazione automatica: ";
        //riciclo type
        std::getline(std::cin, type);
        std::cout << "\n";
        if (type == "\n")   number_of_turns = 10;
        else if (std::stoi(type) > 0)   number_of_turns = std::stoi(type);
        else{
            std::cout << "Valore non valido, procedo in automatico (10 turni)" << "\n";
            number_of_turns = 10;
        }

        CPUPlayer* p1 = dynamic_cast<CPUPlayer*>(p1);
    }
    else if (type == "human" || type == "Human"){

        std::cout << "Se si vuole, inserire il nome per il proprio giocatore, altrimenti continuare [ENTER]: ";
        std::getline(std::cin, type);

        HumanPlayer* p1 = dynamic_cast<HumanPlayer*>(p1);
        p1 -> set_name(type);
    }
    else {
        std::cout << "Errore nell'acquistizione di input. Riprovare da riga di comando" << "\n";
        exit(1);
    }

    CPUPlayer p2;
    CPUPlayer p3;
    CPUPlayer p4;

    Board board(*p1, p2, p3, p4);

    bool done = false;
    while (!done)   done = board.next();

    return 0;
}