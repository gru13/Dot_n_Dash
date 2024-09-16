#include<./Inbulit_types.h>

int initDash(Game* g){
    g->dash = (Dash*)malloc(sizeof(Dash));
    g->dash->x = g->WinX / 2;
    g->dash->y = g->WinY - 2;
    g->dash->Size = 20;
    int y = g->dash->y;
    int x = g->dash->x;
    for(int i = x-10; i <= x+10 ;i++){
        mvwprintw(g->win,y,i,"%s",DASH);
    }
    pthread_create(&g->DashMover_thread, NULL, DashMover, (void*)g);

    return OK;
}   


void* DashMover(void* game){
    Game* g = (Game*)game;
    while(g->gameState != CLOSE){
        choice = wgetch(g->win);
        pthread_mutex_lock(&mutex);
        // mvwprintw(g->win,0,0,"%s",CONT);
        switch (choice){
            case ERR:
                goto ContNextLoopDashMover;
                break;
            case KEY_UP:
                g->gameState = IN_GAME;
                pthread_create(&g->BallMover_thread, NULL, BallMover, (void*)g);
                break;
            case KEY_LEFT:
                // mvwprintw(g->win,0,0,"%s",MV_LFT);
                if(g->dash->x - g->dash->Size/2 >= 2){
                    if(g->gameState == WAIT_TO_START){
                        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",SPC);
                        g->dot->x--;
                        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
                    }
                    mvwprintw(g->win,g->dash->y,g->dash->x + g->dash->Size/2,"%s",SPC);
                    g->dash->x--;
                    mvwprintw(g->win,g->dash->y,g->dash->x - g->dash->Size/2,"%s",DASH);
                }
                break;
            case KEY_RIGHT:
                // mvwprintw(g->win,0,0,"%s",MV_RYT);
                if(g->dash->x + g->dash->Size/2 < g->WinX-2){
                    if(g->gameState == WAIT_TO_START){
                        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",SPC);
                        g->dot->x++;
                        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
                    }
                    mvwprintw(g->win,g->dash->y,g->dash->x - g->dash->Size/2,"%s",SPC);
                    g->dash->x++;
                    mvwprintw(g->win,g->dash->y,g->dash->x + g->dash->Size/2,"%s",DASH);
                }
                break;
            case ESC:
                // mvwprintw(g->win,0,0,"%s",CLOSE);
                g->gameState = CLOSE;
                pthread_mutex_unlock(&mutex);
                goto endLOOPDashMover;
                break;
            default:
                break;
        }
        ContNextLoopDashMover:
            pthread_mutex_unlock(&mutex);
    }
    endLOOPDashMover:
    return NULL;
}

