#include <stdio.h>

#define OPPONENT X
#define PLAYER (OPPONENT == O ? X : O)

#include "board.c"
#include "opponent.c"

int go(Player player){
    if(player == OPPONENT){
        Point opp_pt = opp_move();
        bset(opp_pt, OPPONENT);

        print_board();
    }else if(player == PLAYER){
        move(PLAYER);

        print_board();
    }

    if(is_won()){
        Player winner = get_winner();
        printf("Winner: %c", translate_letter(winner));
        return 1;
    }
    printf("\n\n");
    return 0;
}

int main() {
    init_board();

    int current = OPPONENT;

    while(1) {

        if(go(current)){
            break;
        }

        current = current == PLAYER ? OPPONENT : PLAYER;
    }

    free_board();
    return 0;
}
