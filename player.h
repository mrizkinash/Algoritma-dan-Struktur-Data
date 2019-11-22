#ifndef PLAYER_H
#define PLAYER_H

#include"listlinier.h"
#include"queue.h"
#include"boolean.h"

typedef struct {
    Queue skill;
    boolean turn;
    List listbangunan;
} Player;

#define LB(P) P.listbangunan
#define Turn(P) P.turn
#define Skill(P) P.skill

void InitPlayer (Player *P);

#endif