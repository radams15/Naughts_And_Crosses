#include <ncurses.h>

#define KEY_ESC 27

#define BORDER 5

void gui(){
    WINDOW *w;
    int c;

    Pt p = {0,0};

    initscr();

    w = newwin(0, 0, 5, 5); // make the box with the same height as apps and the same width as the largest app
    box(w, 0, 0);

    for(int y=0 ; y<BOARD_Y*BORDER ; y+=BORDER){
        for(int x=0 ; x<BOARD_X*BORDER ; x+=BORDER){
            mvwprintw(w, y, x, "%c", translate_letter(bget(p)));
        }
    }

    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while(( c = wgetch(w)) != KEY_ESC){

        mvwprintw( w, p.y*BORDER, p.x*BORDER, "%c", translate_letter(bget(p)));

        switch(c) {

            case KEY_DOWN:
                if(p.y != BOARD_Y-1){
                    p.y++;
                }
                break;

            case KEY_UP:
                if(p.y != 0){
                    p.y--;
                }
                break;

            case KEY_LEFT:
                if(p.x != 0){
                    p.x--;
                }
                break;

            case KEY_RIGHT:
                if(p.x != BOARD_X-1){
                    p.x++;
                }
                break;

            case '\n':
                if(bget(p) != NONE){
                    break;
                }
                bset(p, PLAYER);

                Pt op = opp_move(OPPONENT);

                bset(op, OPPONENT);
                mvwprintw( w, op.y*BORDER, op.x*BORDER, "%c", translate_letter(bget(op)));

                break;

            default: break;

        }

        wattron(w, A_STANDOUT);

        mvwprintw( w, p.y*BORDER, p.x*BORDER, "%c", translate_letter(bget(p)));

        wattroff(w, A_STANDOUT);

        if(is_won()){
            break;
        }
    }

    delwin(w);
    endwin();
    printf("Winner: %c\n", translate_letter(get_winner()));
}