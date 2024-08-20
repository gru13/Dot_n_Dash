#include<./Inbulit_types.h>


int main() {
    Game* g = initGame();
    REFRESH;
    sleep(5);
    delwin(g->win);
    return 0;
}