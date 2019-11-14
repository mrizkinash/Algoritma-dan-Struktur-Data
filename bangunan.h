#ifndef BANGUNAN_H
#define BANGUNAN_H

#include "ADT/boolean.h"
#include "ADT/point.h"
#include "array.h"

typedef struct {
	int level;
	boolean shield; //pertahanan
	int army;
	int gain;
	int max;
	int index; // kepemilikan
	char type;
	POINT P;
} Bangunan;

typedef TabInt Bangunan;

#define AbsisBangunan(B) ((B).P).X
#define OrdinatBangunan(B) ((B).P).Y
#define Level(B) (B).level
#define Army(B) (B).army
#define Shield(B) (B).shield
#define Type(B) (B).type
#define Index(B) (B).index


int getArmy(Bangunan B);
boolean getBangunanShield(Bangunan B);
int getBangunanLevel(Bangunan B);
int getBangunanIndex(Bangunan B);
char getBangunanType(Bangunan B);
void setBangunanPoint(Bangunan *B, int X, int Y);
void setBangunanType(Bangunan *B, char CC);
void setBangunanIndex(Bangunan *B,int i);
void initArmy(Bangunan *B, int U);
void setBangunanShield(Bangunan *B, boolean X);
void setBangunanLevel(Bangunan *B, int X);

#endif
