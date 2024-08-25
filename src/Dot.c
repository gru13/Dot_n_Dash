#include<./Inbulit_types.h>
int direction = -1;
int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->x = g->WinX/2 - 0;
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
        if((g->dot->y == 0 || g->dot->y == g->dash->y-1) && (g->dot->x > g->dash->x + g->dash->Size/2 || 
            g->dot->x < g->dash->x - g->dash->Size/2)){
            break;
        }
        pthread_mutex_lock(&mutex);
            pprint(g->dot->y,g->dot->x,SPC);
        if(QueueIsEmpty(g->dot->nxtY) || QueueIsEmpty(g->dot->nxtX)){
            if(g->dot->x == g->WinX/2){
                if(g->dot->y == g->dash->y - 1){
                    direction = -1;
                }else {
                    direction = 1;
                }
                while(TRUE){
                   int newX, newY;
                   if(QueueIsEmpty(g->dot->nxtX)){
                        newX = g->dot->x;
                   }else{
                        newX = QueueRear(g->dot->nxtX);
                   }
                   if(QueueIsEmpty(g->dot->nxtY)){
                        newY = g->dot->y;
                   }else{
                        newY = QueueRear(g->dot->nxtY) + direction;
                   }
                   if(inDotArea(g,newX,newY)){
                        QueueEnqueue(g->dot->nxtX,newX);
                        QueueEnqueue(g->dot->nxtY,newY);
                   }else{
                        break;
                   }
                }
                
            }
        }
        g->dot->x = QueueDequeue(g->dot->nxtX); 
        g->dot->y = QueueDequeue(g->dot->nxtY);
        pprint(g->dot->y,g->dot->x,DOT);
        // REFRESH
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