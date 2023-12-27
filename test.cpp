#include <iostream>
#include <cstdlib> 
#include <ctime>

int main(){
    int i = 2;
    int c = 4;
    std::vector<std::string> words(5);
    words.at(0) = "148";
    words.at(1) = "248";
    words.at(2) = "359";
    words.at(3) = "458";
    words.at(4) = "458";
    
    for (int j = i; j < c; j++){
        if (words.at(j).substr(1) == words.at(j+1).substr(1)){
            c = j; //la prossima iterazione dei nuovi lanci parte da j
            break;
        }   
    }
    std::cout << c;
    return 0;
}