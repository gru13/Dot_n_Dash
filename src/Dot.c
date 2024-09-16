#include "./Inbulit_types.h"

int directionX = -1;
int directionY = -1;
double angle = 90;
int initDot(Game* g){
    g->dot = (Dot*)malloc(sizeof(Dot));
    g->dot->x = g->WinX/2 - g->dash->Size/4;
    // g->dot->x = g->WinX/2;
    g->dot->speed = 200;
    g->dot->directionX = -1;
    g->dot->directionY = -1;
    g->dot->y = g->WinY - 3;
    g->dot->angle = 1.0;
    mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
    pthread_create(&g->BallMover_thread, NULL, BallMover, (void*)g);
    return OK;
}

int hitSomething(Game* g){
    if(g->dot->y == 1){
        return KEY_UP;
    }
    if(g->dot->y == g->dash->y-1){
        return KEY_DOWN;
    }
    if(g->dot->x == 1){
        return KEY_LEFT;
    }
    if(g->dot->x == g->WinX - 2){
        return KEY_RIGHT;
    }

    
}

void changeDirection(Game* g){
    switch (hitSomething(g)){
    case KEY_LEFT:
        g->dot->directionX = 1;
        break;
    case KEY_RIGHT:
        g->dot->directionX = -1;
        break;
    case KEY_UP:
        g->dot->directionY = 1;
        break;
    case KEY_DOWN:
        // g->dot->angle = (float)(g->dash->x - g->dot->x)/(float)g->dash->Size;
        // printf("angle : %f", angle);
        g->dot->directionY = -1;
        break;
    default:
        // didn't hit anything
        break;
    }
}

void* BallMover(void* game){
    Game* g = (Game*)game;
    while(g->gameState == IN_GAME){
        if((g->dot->y == g->dash->y-1) && (g->dot->x > g->dash->x + g->dash->Size/2 ||
            g->dot->x < g->dash->x - g->dash->Size/2)){
            g->gameState = CLOSE;
            break;
        }
        pthread_mutex_lock(&mutex);
        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",SPC);
        changeDirection(g);
        g->dot->x += g->dot->directionX;
        g->dot->y += g->dot->angle*g->dot->directionY;
        mvwprintw(g->win,g->dot->y,g->dot->x,"%s",DOT);
        pthread_mutex_unlock(&mutex);
        // sleep(g->dot->speed);
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