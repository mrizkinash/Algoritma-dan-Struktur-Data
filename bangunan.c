#include <stdio.h>
#include "bangunan.h"

void LevelUpBangunan(Bangunan B){
    if(Type(B)=='C') Army(B)-MC[Level(B)];
	else if(Type(B)=='T') Army(B)-MT[Level(B)];
	else if(Type(B)=='F') Army(B)-MF[Level(B)];
	else if(Type(B)=='V') Army(B)-MV[Level(B)];
    Level(B)+=1;
}
// level +=1
// jumlah pasukan berkurang M/2

Boolean CekBatasPasukan(Bangunan B){
    if(Type(B)=='C') return (Army(B)+AC[Level(B)] < MC[Level(B)]);
	else if(Type(B)=='T') return (Army(B)+AT[Level(B)] < MT[Level(B)]);
	else if(Type(B)=='F') return (Army(B)+AF[Level(B)] < MF[Level(B)]);
	else if(Type(B)=='V') return (Army(B)+AV[Level(B)] < MV[Level(B)]);
}
// Cek apakah nilai dari penambahan pasukan melebihi M
// jika sudah melebihi, stop penambahan

void AddPasukan(Bangunan B){
	if(CekBatasPasukan(B) && Owner(B)!=0){
		if(Type(B)=='C') Army(B)+=AC[Level(B)];
		else if(Type(B)=='T') Army(B)+=AT[Level(B)];
		else if(Type(B)=='F') Army(B)+=AF[Level(B)];
		else if(Type(B)=='V') Army(B)+=AV[Level(B)];
	}
}
// menambahkan A jumlah pasukan ke seluruh bangunan yang dimiliki X pada setiap turn X

void ChangeOwnerB(Bangunan B, int X, int Y){
    Level(B) = 1;
    Army(B) = X;
    Owner(B) = Y;
}
// reset bangunan saat pindah kepemilikan, 
// dengan X sebagai jumlah pasukan yang baru
// dan Y sebagai pemilik yang baru

void MovePasukan(BangArr Br, int X, int Y, int pas){
    Army(Br.arr[X])-=pas;
    Army(Br.arr[Y])+=pas;
}
// memindahkan pas buah pasukan dari bangunan X ke bangunan Y
