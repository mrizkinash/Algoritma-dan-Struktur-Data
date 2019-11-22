#ifndef state_H
#define state_H

#include "arraydin.h"
#include "bangunan.h"
#include "graph.h"
#include "player.h"

typedef struct {
    Player P1,P2;
    TabInt ArrBang;
    MATRIKS peta;
    Graph G; // ini knp
    char lastaction[30];
}state;

#endif