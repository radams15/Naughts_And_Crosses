#include <stdio.h>

#define OPPONENT X
#define PLAYER (OPPONENT == O ? X : O)

#include "board.c"
#include "opponent.c"

#include "gui.c"

int go(Player player){
    if(player == OPPONENT){
        Pt opp_pt = opp_move(OPPONENT);
        bset(opp_pt, player);

        print_board();
    }else if(player == PLAYER){
        move_player(player);

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

void cli(){
    int current = OPPONENT;

    while(1) {

        if(go(current)){
            break;
        }

        current = current == PLAYER ? OPPONENT : PLAYER;
    }
}

int main() {
    init_board();

    gui();

    free_board();
    return 0;
}
