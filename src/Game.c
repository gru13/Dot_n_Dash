#include<./Inbulit_types.h>


Game* initGame(){
    Game* g = (Game*)malloc(sizeof(Game));
    initDisplay(g);
    initDash(g);
    initDot(g);
    return g;
}

int initDisplay(Game* g){
    system(CLEARSCRN);
    g->win = initscr();
    g->WinX = getmaxx(g->win);
    g->WinY = getmaxy(g->win);
    wprintw(g->win,"HEko from display");
    wrefresh(g->win);
    return OK;
}