//
// Created by rhys on 11/08/2020.
//

#include <string.h>

#define MAX_INP 8
#define INPUT_DELIM ","
#define FAIL -5

char* read_points(){
    char s[MAX_INP];
    char* out = calloc(MAX_INP, sizeof(char));

    fgets(s, sizeof(s), stdin);

    strcpy(out, s);

    return out;
}

int* split_points(char* str){
    int* out = calloc(2, sizeof(int));
    char* tok = strtok(str, INPUT_DELIM);

    for(int i=0 ; i<2 ; i++){
        int x = atoi(tok);
        out[i] = x;

        tok = strtok(NULL, INPUT_DELIM);
    }

    return out;
}

Pt get_point(char* prompt){
    if(strlen(prompt) != 0) {
        printf("%s", prompt);
    }
    char* raw = read_points();

    int* points = split_points(raw);
    Pt p;
    p.x = points[0];
    p.y = points[1];
    free(points);
    return p;
}