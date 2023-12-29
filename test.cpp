#include <iostream>
#include <cstdlib> 
#include <ctime>


int main(){

    std::string input;
    std::getline(std::cin, input);
    if (input == "\n")     return 0;
    std::cout << input <<"\n";
    return 0;
}