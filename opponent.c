//
// Created by rhys on 12/08/2020.
//

#include <limits.h>

#define INF INT_MAX

#define WIN 1
#define LOSE -1
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

int minimax(int depth, int maximise){
    int current_score = get_board_val(OPPONENT);
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
                Point p = {x, y};
                if(bget(p) == NONE){
                    bset(p, OPPONENT);

                    top_score = get_max(top_score, minimax(depth+1, !maximise));

                    bset(p, NONE);
                }
            }
        }
    }
    else{
        top_score = INF;
        for(int y=0 ; y<BOARD_Y ; y++){
            for(int x=0 ; x<BOARD_X ; x++){
                Point p = {x, y};
                if(bget(p) == NONE){
                    bset(p, OPPONENT);

                    top_score = get_min(top_score, minimax(depth+1, !maximise));

                    bset(p, NONE);
                }
            }
        }
    }
    return top_score;
}

Point opp_move(){
    int best = -INF;
    Point best_move;
    int mv;

    for(int y=0 ; y<BOARD_Y ; y++){
        for(int x=0 ; x<BOARD_X ; x++){
            Point p = {x, y};
            if(bget(p) == NONE){
                bset(p, OPPONENT);

                mv = minimax(0, 0);

                bset(p, NONE);

                if(mv > best){
                    best_move = p;
                    best = mv;
                }
            }
        }
    }
    printf("Best move: %i\n", best);
    return best_move;
}