#ifndef BANGUNAN_H
#define BANGUNAN_H

#include "ADT/boolean.h"
#include "ADT/point.h"

typedef struct {
    int owner; // 0 -> no owner, 1 -> pemain 1, 2 -> pemain 2
    int army;
	int level;
	char type;
	POINT P;
} Bangunan;

#define AbsisBangunan(B) ((B).P).X
#define OrdinatBangunan(B) ((B).P).Y
#define Level(B) (B).level
#define Army(B) (B).army
#define Defense(B) (B).defense
#define Type(B) (B).type
#define Owner(B) (B).owner

void CreateBangunan (Bangunan *B, char c, int i, int j);
// membuat inisialisasi bangunan pada awal input
void LevelUpBangunan(Bangunan B);
// level +=1
// jumlah pasukan berkurang M/2
Boolean CekBatasPasukan(Bangunan B);
// Cek apakah nilai dari penambahan pasukan melebihi M
// jika sudah melebihi, stop penambahan
void AddPasukan(Bangunan B);
// menambahkan A jumlah pasukan ke bangunan B
void ChangeOwnerB(Bangunan B, int X, int Y);
// reset bangunan saat pindah kepemilikan, 
// dengan X sebagai jumlah pasukan yang baru
// dan Y sebagai pemilik yang baru
void MovePasukan(Bangunan B1, Bangunan B2, int X);
// memindahkan X buah pasukan dari bangunan B1 ke bangunan B2

#endif
