#include <iostream>
int main(){

    std::string prova = "ciao";
    prova.erase(prova.begin()+2, prova.begin()+2);
    std::cout << prova;
}