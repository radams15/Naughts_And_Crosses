//
// Created by rhys on 11/08/2020.
//

#include <stdlib.h>
#include <stdio.h>

#define Player int

#include "point.c"
#include "parsing.c"

#define BOARD_X 3
#define BOARD_Y 3

int** board;

enum Letters{
    X = 1,
    O = 2,
    NONE = -1,

    X_CHR = 'X',
    O_CHR = 'O',
    NONE_CHR = ' '
};

void init_board(){
    board = calloc(BOARD_Y, sizeof(int*));

    for(int y=0 ; y < BOARD_Y ; y++){
        board[y] = calloc(1, sizeof(int));

        for(int x=0 ; x<BOARD_X ; x++) {
            board[y][x] = NONE;
        }
    }
}

char translate_letter(Player letter){
    if(letter == X){
        return X_CHR;
    }else if(letter == O){
        return O_CHR;
    }else if(letter == NONE){
        return NONE_CHR;
    }else{
        return '?';
    }
}

void bset(Point p, int val){
    if((val == X || val == O || val == NONE) && (p.x >= 0) && (p.y >= 0) && (p.x <= BOARD_X) && (p.y <= BOARD_Y)) {
        board[p.y][p.x] = val;
    }
}

int bget(Point p){
    if((p.x >= 0) && (p.y >= 0) && (p.x <= BOARD_X) && (p.y <= BOARD_Y)) {
        return board[p.y][p.x];
    }
    return -1;
}

int bgetv(int x, int y){
    Point p = {x, y};
    return bget(p);
}

void print_board(){
    printf("______________\n");
    for(int y=0 ; y<BOARD_Y ; y++){
        for(int x=0 ; x<BOARD_X ; x++){
            Point p;
            p.x = x;
            p.y = y;
            printf("| %c ", translate_letter(bget(p)));
            //printf("| %i ", bget(p));
        }
        printf("|\n");
    }
    printf("______________\n");
}

int move(Player player){
    while(1) {
        printf("%c ", translate_letter(player));
        Point p = get_point("=> ");
        if(p.x == FAIL && p.y == FAIL){
            printf("Please Enter A Valid Set Of Numbers\n");
            continue;
        }

        if (p.x == -1 || p.y == -1) {
            return -1;
        }

        if(bget(p) == NONE){
            bset(p, player);
        }else{
            printf("Point already Taken! Try Again.\n");
            continue;
        }

        break;
    }
    return 0;
}

Player get_winner(){
    for(int y=0 ; y<BOARD_Y ; y++){
        if(bgetv(0, y) == bgetv(1, y) == bgetv(2, y) && bgetv(0, y) != NONE){
            return bgetv(0, y);
        }
    }
    for(int x=0 ; x<BOARD_X ; x++){
        if(bgetv(x, 0) == bgetv(x, 1) == bgetv(x, 2)  && bgetv(x, 0) != NONE){
            return bgetv(x, 0);
        }
    }
    if(bgetv(0, 0) == bgetv(1, 1) == bgetv(2, 2)  && bgetv(0, 0) != NONE){
        return bgetv(0, 0);
    }
    if(bgetv(0, 2) == bgetv(1, 1) == bgetv(2, 0)  && bgetv(0, 2) != NONE){
        return bgetv(0, 2);
    }
    return NONE;
}

int is_won(){
    return get_winner() != NONE;
}

int spaces_left(){
    board = calloc(BOARD_Y, sizeof(int*));

    for(int y=0 ; y < BOARD_Y ; y++){
        board[y] = calloc(1, sizeof(int));

        for(int x=0 ; x<BOARD_X ; x++) {
            if(board[y][x] == NONE){
                return 1;
            }
        }
    }
    return 0;
}


void free_array(int** arr, int size){
    for(int i=0 ; i<size ; i++){
        free(board[i]);
    }
    free(board);
}

void free_board(){
    free_array(board, BOARD_Y);
}

int** get_board_copy(){
    int** dup = malloc(BOARD_Y * BOARD_X * sizeof(int));
    memcpy(dup, board, BOARD_X*BOARD_Y*sizeof(int));
    return dup;
}