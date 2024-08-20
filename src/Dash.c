#include<./Inbulit_types.h>

int initDash(Game* g){
    g->dash = (Dash*)malloc(sizeof(Dash));
    g->dash->x = g->WinX / 2;
    g->dash->y = g->WinY - 2;
    g->dash->Size = 20;
    int y = g->dash->y;
    int x = g->dash->x;
    for(int i = x-10; i < x+10 ;i++){
        pprint(y,i,DASH);
    }

    pthread_create(&g->DashMover_thread, NULL, DashMover, (void*)g);

    return OK;
}


void* DashMover(void* game){
    Game* g = (Game*)game;
    while(TRUE){
        pthread_mutex_lock(&mutex);
        pprint(0,0,CONT);REFRESH;
        choice = wgetch(g->win);
        switch (choice){
            case ERR:
                goto endLOOPListner;
                break;
            case KEY_LEFT:
                pprint(0,0,MV_LFT);
                if(g->dash->x - g->dash->Size/2 >= 2){
                    pprint(g->dash->y,g->dash->x + g->dash->Size/2,SPC);
                    g->dash->x--;
                    pprint(g->dash->y,g->dash->x - g->dash->Size/2,DASH);
                }
                break;
            case KEY_RIGHT:
                pprint(0,0,MV_RYT);
                if(g->dash->x + g->dash->Size/2 < g->WinX-2){
                    pprint(g->dash->y,g->dash->x - g->dash->Size/2,SPC);
                    g->dash->x++;
                    pprint(g->dash->y,g->dash->x + g->dash->Size/2,DASH);
                }
                break;
            case ESC:
                pprint(0,0,CLOSE);
                goto EndLOOP;
                break;
            default:
                pprint(0,0,CONT);
                break;
        }
        endLOOPListner:
            REFRESH;
            // sleep(1);    
            pthread_mutex_unlock(&mutex);
    }
    EndLOOP:
            pthread_mutex_unlock(&mutex);

    return NULL;
}