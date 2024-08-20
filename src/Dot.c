#include<./Inbulit_types.h>

int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->x = g->WinX/2;
    g->dot->y = g->WinY - 3;
    mvwaddch(g->win,g->dot->y,g->dot->x,'@');
    return OK;
}