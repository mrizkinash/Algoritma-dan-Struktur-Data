#ifndef BANGUNAN_H
#define BANGUNAN_H

#include "boolean.h"
#include "point.h"

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


#include <stdio.h>
#include "bangunan.h"

int GetA(Bangunan B);
// mereturn nilai penambahan pasukan / A dari Bangunan B sesuai dengan levelnya

int GetM(Bangunan B);
// mereturn nilai Maksimum penambahan pasukan dari Bangunan B sesuai dengan levelnya

boolean GetP(Bangunan B);
// mereturn ada atau tidaknya pertahanan dari Bangunan B sesuai dengan levelnya

void CreateBangunan (Bangunan *B, char c, int i, int j);
// aksi : menginisialisasi type, point, level, dan pasukan pada bangunan B
// I.S. bangunan belum di inisialisasi
// F.s. terbentuk bangunan

void LevelUpBangunan(Bangunan *B);
// menaikan level suatu bangunan dengan syarat pasukannya 
// sudah lebih dari setengah M bangunan tsb
// I.S. bangunan terdefinisi
// F.s bangunan naik level, dan pasukannya berkurang

boolean CekBatasPasukan(Bangunan B);
	// Cek apakah nilai dari penambahan pasukan melebihi M
	// jika sudah melebihi, stop penambahan

void AddPasukan(Bangunan *B);
// menambahkan A jumlah pasukan ke bangunan dengan syarat
// bangunan sudah berkepemilikan
// I.S. bangunan terdefinisi
// F.S pasukan pada bangunan bertambah sebanyak A pada setiap turn

void ChangeOwnerB(Bangunan *B, int X, int Y);
// reset bangunan saat pindah kepemilikan, 
// dengan X sebagai jumlah pasukan yang baru
// dan Y sebagai pemilik yang baru
// I.S. bangunan terdefinisi
// F.S. pemilik B berubah dari X menjadi Y

void MovePasukan(Bangunan *B1, Bangunan *B2, int x);
// memindahkan X buah pasukan dari bangunan B1 ke bangunan B2
// I.S. 2 Bangunan terdefinsi
// F.S. pasukan B1 berkurang sebanyak x dan pasukan B2 bertambah sebanyak y

void CetakBangunan(Bangunan B);
// mencetak bagunan dengan format:
// <no> <tipe bangunan> <(point)> <pasukan> <level>
// I.S. bangunan terdefinisi
// F.S tercetak isi bangunan B

#endif
