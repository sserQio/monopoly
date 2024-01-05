#include "board.cpp"
#include "cpuplayer.cpp"
#include "humanplayer.cpp"


int main(){

    Player p1, p2, p3, p4;
    Board board(p1,p2,p3,p4);
    board.next();
    board.print_board();
    return 0;
}