#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    Queue skill;
    boolean turn;
    List listbangunan;
} player;

#define LB(P) P.listbangunan
#define Turn(P) P.turn
#define Skill(P) P.skill

#endif