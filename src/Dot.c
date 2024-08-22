#include<./Inbulit_types.h>

int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->x = g->WinX/2;
    g->dot->y = g->WinY - 3;
    g->dot->nxtX = (Queue*)malloc(sizeof(Queue));
    g->dot->nxtY = (Queue*)malloc(sizeof(Queue));
    QueueInit(g->dot->nxtX);
    QueueInit(g->dot->nxtY);
    mvwaddch(g->win,g->dot->y,g->dot->x,DOT);
    pthread_create(&g->BallMover_thread, NULL, BallMover, (void*)g);
    return OK;
}


void* BallMover(void* game){
    Game* g = (Game*)game; 
    while(TRUE){
        if(g->dot->y == 1 || g->dot->x == 1){
            break;
        }
        pthread_mutex_lock(&mutex);
        pprint(g->dot->y,g->dot->x,SPC);
        if(QueueIsEmpty(g->dot->nxtY)){
            g->dot->y--;
        }
        if(QueueIsEmpty(g->dot->nxtX)){
            g->dot->x--;
        }
        pprint(g->dot->y,g->dot->x,DOT);
        // REFRESH
        pthread_mutex_unlock(&mutex);
        // sleep(250);
        sleep(200);

    }
    return NULL;
}