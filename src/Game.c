#include<./Inbulit_types.h>

Game* initGame(){
    char CharBuffer[101];
    Game* g = (Game*)malloc(sizeof(Game));
    initDisplay(g);
    initDash(g);
    initDot(g);
    REFRESH;
    curs_set(FALSE);//setting cursor hidden
    return g;
}

int initDisplay(Game* g){
    system(CLEARSCRN);
    g->win = initscr();
    g->WinX = getmaxx(g->win);
    g->WinY = getmaxy(g->win);
    for(int i = 0; i < g->WinX; i++){  
        piprint(g->WinY-1,i,HOR_LINE);
        piprint(0,i,HOR_LINE);
    }
    for(int i = 0; i < g->WinY; i++){
        piprint(i,g->WinX-1,VER_LINE);
        piprint(i,0,VER_LINE);
    }
    return OK;
}