#include<./Inbulit_types.h>


int main() {
    Game* g = initGame();
    REFRESH;
    pthread_join(g->DashMover_thread,NULL);
    pthread_join(g->BallMover_thread,NULL);
    sleep(500);
    end:
        delwin(g->win);
    return 0;
}