#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<string.h>


// #define REFRESH_RATE 4000 // this in milli-second
#define SPC 32	 // ' '
#define DASH 219 // █
#define DOT 79	 // O
// #define BALL 254	 // ■
// #define DOT 254	 // ■
// #define DASH  220 // ▄

#define BLOK 219 // █
#define VER_LINE 186 // ║
#define HOR_LINE 205 // ═
#define TL_COR 201	 // ╔
#define BL_COR 200	 // ╚
#define TR_COR 187	 // ╗
#define BR_COR 188	 // ╝


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
#else
    #define CLEARSCRN "cls"
#endif



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
