#include<./Inbulit_types.h>

Game* initGame(){
    char CharBuffer[101];
    Game* g = (Game*)malloc(sizeof(Game));
    mutex = PTHREAD_MUTEX_INITIALIZER;
    initDisplay(g);
    initDash(g);
    initDot(g);
    REFRESH;
    curs_set(FALSE);//setting cursor hidden
    noecho();
    nodelay(g->win, TRUE);
    keypad(g->win, TRUE);



    REFRESH;
    return g;
}

int initDisplay(Game* g){
    system(CLEARSCRN);
    g->win = initscr();
    g->WinX = getmaxx(g->win);
    g->WinY = getmaxy(g->win);
    // wborder(g->win,VER_LINE,VER_LINE,HOR_LINE,HOR_LINE,TL_COR,TR_COR,BL_COR,BR_COR);
    for(int i = 0; i < g->WinX; i++){  
        pprint(g->WinY-1,i,HOR_LINE);
        pprint(0,i,HOR_LINE);
    }
    for(int i = 0; i < g->WinY; i++){
        pprint(i,g->WinX-1,VER_LINE);
        pprint(i,0,VER_LINE);
    }
    return OK;
}


void* StartGame(void* game){
    Game* g = (Game*)game;
    while(TRUE){
        if(choice == CLOSE){
            break;
        }
        
    }
    return OK;
}


