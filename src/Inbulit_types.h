#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<pthread.h>
#include<math.h>

#define INITIAL_CAPACITY 100
#define INCREMENT 20
extern char CharBuffer[INITIAL_CAPACITY];
// #define REFRESH_RATE 4000 // this in milli-second
#define SPC " "
// #define DOT "■"
#define DOT "⬤"
#define DASH "█"
#define VER_LINE "║"
#define HOR_LINE "═"
#define TL_COR  "╔"
#define BL_COR  "╚"
#define TR_COR  "╗"
#define BR_COR  "╝"


#define PI 3.14159265358979323846

#define MV_LFT 'L'
#define MV_RYT 'R'
#define MV_UPP 'U'
#define MV_DWN 'D'
#define CONT 'c'
#define CLOSE 'x'
#define ESC 27
#define OK 0
#define ERRO 1
#define WAIT_TO_START 'w'
#define IN_GAME 'g'



#ifdef __linux__
    #define CLEARSCRN "clear"
    #include<ncurses.h>
    #include<unistd.h>
#elif defined(_WIN32)
    #define sleep(time) Sleep((DWORD)(time));
    #define CLEARSCRN "cls"
    #include<windows.h>
    #include<curses.h>
#endif

//  Init the mutex variable
pthread_mutex_t mutex;
int choice;




typedef struct Dash_Struct{
    int x;
    int y;
    unsigned short Size;
} Dash;

typedef struct Dot_Struct{
    int x;
    int y;
    int directionX;
    int directionY;
    float angle;
    int speed;
} Dot;

typedef struct Game{
    WINDOW* win;
    pthread_t DashMover_thread;
    pthread_t BallMover_thread;
    pthread_t refresh_Thread;
    Dash* dash;
    Dot* dot;
    int gameState;
    unsigned short WinY; // max heigth of current Display
    unsigned short WinX; // max width of current Display
} Game;

/*
        Game.c
overall game function
contains
    init of game
    dealing with board and sync of dash and dots
*/
Game* initGame();
int initDisplay(Game* g);
void* refreshThread(void* game);

/*
        Dash.c

*/
int initDash(Game* g);
void* DashMover(void* game);



/*
        Dot.
*/
int initDot(Game* g);
void* BallMover(void* game);
int inDotArea(Game* g, int x, int y);


/*
    dataStructures.c

    Data Structures:
        Stack
        Queue
*/