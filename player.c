#include "player.h"

void InitPlayer (Player *P) {
    CreateEmptyLB(&(P->listbangunan));
    CreateEmptyQueue(&(P->skill), 10);
    P->turn = false;
    P->et = false;
    P->shieldturn=0;
}