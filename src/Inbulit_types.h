#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>


extern char CharBuffer[101];

// #define REFRESH_RATE 4000 // this in milli-second
#define SPC 32	 // ' '
#define DASH 35 // #
#define DOT 79	 // O
#define VER_LINE '|' // ║
#define HOR_LINE '-' // ═

// #define DASH 219 // █
// #define BALL 254	 // ■
// #define DOT 254	 // ■
// #define DASH  220 // ▄

// #define HOR_LINE 205 // ═
// #define BLOK 219 // █
// #define VER_LINE 186 // ║
// #define TL_COR 201	 // ╔
// #define BL_COR 200	 // ╚
// #define TR_COR 187	 // ╗
// #define BR_COR 188	 // ╝


#define PI 3.14159265358979323846

#define MV_LFT 'L'
#define MV_RYT 'R'
#define MV_UPP 'U'
#define MV_DWN 'D'
#define CONT 'c'
#define CLOSE 'x'
#define OK 0
#define ERRO 1

#ifdef __linux__
    #define CLEARSCRN "clear"
    #include<ncurses.h>
    #include<unistd.h>
#elif defined(_WIN32)
    #define sleep(time) Sleep((DWORD)(time)*1000);
    #define CLEARSCRN "cls"
    #include<windows.h>
    #include<curses.h>
#endif


#define REFRESH wrefresh(g->win);

#define print(str) \
    wprintw((WINDOW*)g->win,"%c",(char)str);
#define pprint(Loc, str) \
    mvwprintw(g->win, (int)Location.(y), (int)Location.(x), "%c", (char)(str))
#define piprint(y,x, str) \
    mvwprintw(g->win, (int)y, (int)x, "%c", (char)(str))

typedef struct Point_Struct{
    int x;
    int y;
} Point;


typedef struct Dash_Struct{
    Point Location;
    unsigned short Size;
} Dash;

typedef struct Dot_Struct{
    Point Location;
} Dot;

typedef struct Game{
    WINDOW* win;
    Dash* dash;
    Dot* dot;
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



/*
        Dash.c 

*/
int initDash(Game* g);



/*
        Dot.    
*/
int initDot(Game* g);
