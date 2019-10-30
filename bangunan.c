#include "bangunan.h"
#include "boolean.h"
#include "point.h"

int getArmy(Bangunan B)
{
	return(Army(B));
}

boolean getBangunanShield(Bangunan B)
{
	return(Shield(B));
}
int getBangunanLevel(Bangunan B)
{
	return (Level(B));
}
int getBangunanIndex(Bangunan B)
{
	return (Index(B));
}
char getBangunanType(Bangunan B)
{
	return (Type(B));
}
void setBangunanPoint(Bangunan *B, int X, int Y)
{
	AbsisBangunan(*B) = X;
	OrdinatBangunan(*B) = Y;
}
void setBangunanType(Bangunan *B, char CC)
{
	Type(*B) = CC;
}
void setBangunanIndex(Bangunan *B,int i)
{
	Index(*B) = i;
}
void initArmy(Bangunan *B, int U)
{
	Army(*B) = U;
}
void setBangunanShield(Bangunan *B, boolean X)
{
	Shield(*B) = X;
}
void setBangunanLevel(Bangunan *B, int X)
{
	Level(*B) = X;
}	
