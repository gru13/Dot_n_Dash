#include "./Inbulit_types.h"

int directionX = -1;
int directionY = -1;
double angle = 90;
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
    while(g->gameState == IN_GAME){
        if((g->dot->y == 0 || g->dot->y == g->dash->y-1) && (g->dot->x > g->dash->x + g->dash->Size/2 || 
            g->dot->x < g->dash->x - g->dash->Size/2)){
            g->gameState = CLOSE;
            break;
        }
        pthread_mutex_lock(&mutex);
        pprint(g->dot->y,g->dot->x,SPC);
        if(QueueIsEmpty(g->dot->nxtY) || QueueIsEmpty(g->dot->nxtX)){
            // if the ball in last layer above the dash layer
            if(g->dot->y == g->dash->y - 1){
                printf("Down ");
                directionY = -1;
                if(g->dot->x == g->dash->x){
                    angle = 90.0; 
                }else{
                    int x = (g->dash->x + g->dash->Size/2) - g->dot->x; // ../refresh math-motion-dot.png
                    angle = atan((double)x/(double)g->dash->Size) ; // multiply this to get in angle  ->  * 180 / PI
                    if(g->dot->x < g->dash->x){
                        
                        directionX = -1;
                        angle -= 3.14159;
                    }else if(g->dot->x > g->dash->x){
                        printf("");
                        directionX = 1;
                    }else if(g->dot->x == g->dash->x){
                        printf("");
                        directionX = 0;
                    }
                }
            }
            // if in topest layer
            else if(g->dot->y == 1){
                directionY = 1;
                if(g->dot->x == g->WinX/2){
                    angle = 90.0; 
                    directionX = 0;
                }else{
                    int x = (g->dash->x + g->dash->Size/2) - g->dot->x; // ../refresh math-motion-dot.png
                    angle = atan((double)x/(double)g->dash->Size) ; // multiply this to get in angle  ->  * 180 / M_PI
                    if(g->dot->x < g->WinX/2){
                        printf("up\n");
                        directionX = -1;
                        angle -= 3.14159;
                    }else if(g->dot->x > g->WinX/2){
                        printf("Down\n");
                        directionX = 1;
                    }
                }
            }
            //  left
            else if(g->dot->x == 1){
                directionX = 1;
                if(g->dot->y == g->WinY/2){
                    angle = 90.0;
                    directionY = 0;
                }else{
                    printf("LEFT : ");
                    int x = (g->dash->x + g->dash->Size/2) - g->dot->x; // ../refresh math-motion-dot.png
                    angle = atan((double)x/(double)g->dash->Size) ; // multiply this to get in angle  ->  * 180 / M_PI
                    if(g->dot->y < g->WinY/2){
                        printf("above\n");
                        directionY = +1;
                        // angle -= 3.14159;
                    }else if(g->dot->y > g->WinY/2){
                        printf("below\n");
                        directionX = -1;
                    }
                }
            }
            //  rigth
            else if(g->dot->x == 1){
                directionX = -1;
                if(g->dot->y == g->WinY/2){
                    angle = 90.0; 
                }else{
                    int x = (g->dash->x + g->dash->Size/2) - g->dot->x; // ../refresh math-motion-dot.png
                    angle = atan((double)x/(double)g->dash->Size) ; // multiply this to get in angle  ->  * 180 / M_PI
                    if(angle*180/PI > 90){
                        directionY= +1;
                    }else if(angle*180/PI < 90){
                        directionY = -1;
                    }
                }
            }
            // simulation move
            printf("%lf , x => %d, y = %d\n",(angle == 90)?90:angle*180/PI, directionX,      directionY);
            int newX,newY, i = 1;
            while(TRUE){
                newX = g->dot->x + i*directionX*((angle == 90.0)?0:1);
                newY = g->dot->y + (int)(i*((angle == 90.0?1:tan(angle)))*directionY);
                if(inDotArea(g,newX,newY)){
                    QueueEnqueue(g->dot->nxtX,newX);
                    QueueEnqueue(g->dot->nxtY,newY);
                }else{
                    break;
                }
                i++;
            }
        }
        if(QueueIsEmpty(g->dot->nxtY) || QueueIsEmpty(g->dot->nxtX)){
            pthread_mutex_unlock(&mutex);
            sleep(100);
            break;
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