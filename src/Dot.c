#include<./Inbulit_types.h>

int initDot(Game* G){
    G->dot = (Dot*)malloc(sizeof(Dot));
    printf("heko from Dot\n");
    return OK;
}