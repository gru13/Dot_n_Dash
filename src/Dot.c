#include<./Inbulit_types.h>

int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->Location.x = g->WinX/2;
    g->dot->Location.y = g->WinY - 3;
    mvwaddch(g->win,g->dot->Location.y,g->dot->Location.x,'@');
    return OK;
}