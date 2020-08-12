//
// Created by rhys on 12/08/2020.
//

#include <limits.h>

#define INF INT_MAX

#define WIN 5
#define LOSE -5
#define NO_RESULT 0

int get_board_val(Player desired_winner){
    if(is_won()) {
        Player winner = get_winner();
        if(winner == desired_winner){
            return WIN;
        }
        return LOSE;
    }
    return NO_RESULT;
}

int get_max(int y, int z){
    if(y > z){
        return y;
    }
    return z;
}
int get_min(int y, int z){
    if(y < z){
        return y;
    }
    return z;
}

int minimax(int depth, int maximise, Player desired_winner){
    int current_score = get_board_val(desired_winner);

    if(current_score != NO_RESULT){
        return current_score;
    }

    /*if(!spaces_left()){
        return NO_RESULT;
    }*/

    int top_score;
    if(maximise){
        top_score = -INF;
        for(int y=0 ; y<BOARD_Y ; y++){
            for(int x=0 ; x<BOARD_X ; x++){
                Pt p = {x, y};
                if(bget(p) == NONE){
                    bset(p, desired_winner);

                    top_score = get_max(top_score, minimax(depth+1, !maximise, desired_winner));

                    bset(p, NONE);
                }
            }
        }
    }
    else{
        top_score = INF;
        for(int y=0 ; y<BOARD_Y ; y++){
            for(int x=0 ; x<BOARD_X ; x++){
                Pt p = {x, y};
                if(bget(p) == NONE){
                    bset(p, desired_winner);

                    top_score = get_min(top_score, minimax(depth+1, !maximise, desired_winner));

                    bset(p, NONE);
                }
            }
        }
    }
    return top_score;
}

Pt opp_move(Player desired_winner){
    int best = -INF;
    Pt best_move;
    int mv;

    for(int y=0 ; y<BOARD_Y ; y++){
        for(int x=0 ; x<BOARD_X ; x++){
            Pt p = {x, y};
            if(bget(p) == NONE){
                bset(p, desired_winner);

                mv = minimax(0, 0, desired_winner);

                bset(p, NONE);

                if(mv > best){
                    best_move = p;
                    best = mv;
                }
            }
        }
    }
    return best_move;
}