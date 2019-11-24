#ifndef saveload_H
#define saveload_H
	
#include "mesinkata.h"
#include "state.h"
#include "stackt.h"
#include "boolean.h"

int KarakterToInt (char CC);

int KataToInt (Kata CKata);

void ReadMatriksSize(MATRIKS *M);

void ReadBangunan(state *S);

void ReadGraph(Graph *G, int size);

void LoadPlayer(Player *P);

void LoadBangunan(state *S);

void LoadGraph(Graph *G);

void SAVEGAME(state S);

void LOADGAME(state *S);

#endif