#include<./Inbulit_types.h>

Game* initGame(){
    char CharBuffer[101];
    Game* g = (Game*)malloc(sizeof(Game));
    g->gameState = WAIT_TO_START;
    mutex = PTHREAD_MUTEX_INITIALIZER;
    initDisplay(g);
    pthread_create(&g->refresh_Thread,NULL,refreshThread,(void*)g);
    initDash(g);
    initDot(g);
    curs_set(FALSE);//setting cursor hidden
    noecho();
    nodelay(g->win, TRUE);
    keypad(g->win, TRUE);
    return g;
}

int initDisplay(Game* g){
    system(CLEARSCRN);
    g->win = initscr();
    g->WinX = getmaxx(g->win);
    g->WinY = getmaxy(g->win);
    // wborder(g->win,VER_LINE,VER_LINE,HOR_LINE,HOR_LINE,TL_COR,TR_COR,BL_COR,BR_COR);
    for(int i = 0; i < g->WinX; i++){  
        mvwprintw(g->win,g->WinY-1,i,"%s",HOR_LINE);
        mvwprintw(g->win,0,i,"%s",HOR_LINE);
    }
    for(int i = 0; i < g->WinY; i++){
        mvwprintw(g->win,i,g->WinX-1,"%s",VER_LINE);
        mvwprintw(g->win,i,0,"%s",VER_LINE);
    }
    mvwprintw(g->win,0,0,"%s",TL_COR);
    mvwprintw(g->win,0,g->WinX-1,"%s",TR_COR);
    mvwprintw(g->win,g->WinY-1,0,"%s",BL_COR);
    mvwprintw(g->win,g->WinY-1,g->WinX-1,"%s",BR_COR);
    return OK;
}

void* refreshThread(void* game){
    Game* g = (Game*)game;
    while(TRUE){
        pthread_mutex_lock(&mutex);
        wrefresh(g->win);
        pthread_mutex_unlock(&mutex);
        sleep(200);
    }
}

