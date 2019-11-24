#ifndef PLAYER_H
#define PLAYER_H

#include"listlinier.h"
#include"queue.h"
#include"boolean.h"

typedef struct {
    Queue skill;
    boolean turn;
    List listbangunan;
    boolean et;
    int shieldturn;
} Player;

#define LB(P) P.listbangunan
#define Turn(P) P.turn
#define Skill(P) P.skill
#define ET(P) P.et

void InitPlayer (Player *P);

#endif