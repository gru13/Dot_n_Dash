#include<./Inbulit_types.h>


int main() {
    Game* g = initGame();
    REFRESH;
    pthread_join(g->DashMover_thread,NULL);
    // sleep(5);
    end:
        delwin(g->win);
    return 0;
}