#include "./Inbulit_types.h"

int directionX = -1;
int directionY = -1;
double angle = 90;
int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->x = g->WinX/2 - g->dash->Size/2 + 1;
    g->dot->directionX = -1;
    g->dot->directionY = -1;
    g->dot->y = g->WinY - 3;
    g->dot->angle = 0;
    // g->dot->nxtX = (Queue*)malloc(sizeof(Queue));
    // g->dot->nxtY = (Queue*)malloc(sizeof(Queue));
    // QueueInit(g->dot->nxtX);
    // QueueInit(g->dot->nxtY);
    mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
    pthread_create(&g->BallMover_thread, NULL, BallMover, (void*)g);
    return OK;
}



void* BallMover(void* game){
    Game* g = (Game*)game; 
    while(g->gameState == IN_GAME){
        if((g->dot->y == 0 || g->dot->y == g->dash->y-1) && (g->dot->x > g->dash->x + g->dash->Size/2 || 
            g->dot->x < g->dash->x - g->dash->Size/2)){
            g->gameState = CLOSE;
            break;
        }
        pthread_mutex_lock(&mutex);
        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",SPC);
        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
        pthread_mutex_unlock(&mutex);
        sleep(100);
    }
    return NULL;
}


int inDotArea(Game* g, int x, int y){  
    if(!(x >= 1 && y >= 1 && x < g->WinX-1 && y < g->WinY-1)){
        return FALSE;
    }   
    if(y < g->dash->y - 1){
        return TRUE;
    }else if(y == g->dash->y - 1 && x >= g->dash->x - g->dash->Size/2 && x <= g->dash->x + g->dash->Size/2){
        return TRUE;
    }else{
        return FALSE;
    }
}
            // if(g->dot->x == g->WinX/2){
            //     if(g->dot->y == g->dash->y - 1){
            //         direction = -1;
            //     }else {
            //         direction = 1;
            //     }
            //     while(TRUE){
            //        int newX, newY;
            //        if(QueueIsEmpty(g->dot->nxtX)){
            //             newX = g->dot->x;
            //        }else{
            //             newX = QueueRear(g->dot->nxtX);
            //        }
            //        if(QueueIsEmpty(g->dot->nxtY)){
            //             newY = g->dot->y;
            //        }else{
            //             newY = QueueRear(g->dot->nxtY) + direction;
            //        }
            //        if(inDotArea(g,newX,newY)){
            //             QueueEnqueue(g->dot->nxtX,newX);
            //             QueueEnqueue(g->dot->nxtY,newY);
            //        }else{
            //             break;
            //        }
            //     }
                
            // }