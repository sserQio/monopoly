#include <iostream>
#include <cstdlib> 
#include <ctime>

int main(){
    int i = 2;

    std::string s = "a2cd";
    if (s[1] == *std::to_string(i).c_str())   s[1] = '\0';
    int n = s.length();
    std::cout << n <<"\n";
    return 0;
}