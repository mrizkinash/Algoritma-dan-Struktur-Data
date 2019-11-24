#ifndef state_H
#define state_H

#include "arraydin.h"
#include "bangunan.h"
#include "graph.h"
#include "player.h"
#include "matriks.h"

typedef struct {
    Player P1,P2;
    TabInt ArrBang;
    MATRIKS M;
    Graph G; 
}state;

#endif