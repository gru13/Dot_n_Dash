#include <./Inbulit_types.h>


int main() {
    Game* g = initGame();
    // pthread_join(g->DashMover_thread,NULL);
    // pthread_join(g->BallMover_thread,NULL);
    while(g->gameState != CLOSE){}
    sleep(500);
    end:
        delwin(g->win);
    return 0;
}