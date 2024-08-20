#include<./Inbulit_types.h>

int initDash(Game* g){
    g->dash = (Dash*)malloc(sizeof(Dash));
    g->dash->Location.x = g->WinX / 2;
    g->dash->Location.y = g->WinY - 2;
    g->dash->Size = 20;
    int y = g->dash->Location.y;
    int x = g->dash->Location.x;
    for(int i = x-10; i < x+10 ;i++){
        piprint(y,i,DASH);
    }
    return OK;
}