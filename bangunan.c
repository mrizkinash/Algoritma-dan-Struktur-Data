#include <stdio.h>
#include "bangunan.h"

void CreateBangunan (Bangunan *B, char c, int i, int j){
	Type(*B) = c;
    AbsisBangunan(*B) = i;
    OrdinatBangunan(*B) = j;
	Level(*B)=1;
	if(Type(*B)=='C') Army(*B)=40;
	else if(Type(*B)=='T') Army(*B)=30;
	else if(Type(*B)=='F') Army(*B)=80;
	else if(Type(*B)=='V') Army(*B)=20;
}

void LevelUpBangunan(Bangunan *B){
    if(Type(*B)=='C') Army(*B)-(0.5 * MC[Level(*B)]);
	else if(Type(*B)=='T') Army(*B)-(0.5 * MT[Level(*B)]);
	else if(Type(*B)=='F') Army(*B)-(0.5 * MF[Level(*B)]);
	else if(Type(*B)=='V') Army(*B)-(0.5 * MV[Level(*B)]);
    Level(*B)+=1;
}
// level +=1
// jumlah pasukan berkurang M/2

boolean CekBatasPasukan(Bangunan B){
    if(Type(B)=='C') return (Army(B)+AC[Level(B)] >= MC[Level(B)]);
	else if(Type(B)=='T') return (Army(B)+AT[Level(B)] >= MT[Level(B)]);
	else if(Type(B)=='F') return (Army(B)+AF[Level(B)] >= MF[Level(B)]);
	else if(Type(B)=='V') return (Army(B)+AV[Level(B)] >= MV[Level(B)]);
}
// Cek apakah nilai dari penambahan pasukan melebihi M
// jika sudah melebihi, stop penambahan



void AddPasukan(Bangunan *B){
	if(CekBatasPasukan(*B) && Owner(*B)!=0){
		if(Type(*B)=='C') Army(*B)+=AC[Level(*B)];
		else if(Type(*B)=='T') Army(*B)+=AT[Level(*B)];
		else if(Type(*B)=='F') Army(*B)+=AF[Level(*B)];
		else if(Type(*B)=='V') Army(*B)+=AV[Level(*B)];
	}
}
// menambahkan A jumlah pasukan ke seluruh bangunan yang dimiliki X pada setiap turn X

void ChangeOwnerB(Bangunan *B, int X, int Y){
    Level(*B) = 1;
    Army(*B) = X;
    Owner(*B) = Y;
}
// reset bangunan saat pindah kepemilikan, 
// dengan X sebagai jumlah pasukan yang baru
// dan Y sebagai pemilik yang baru

void MovePasukan(Bangunan *B1, Bangunan *B2, int x){
	Army(*B1)-=x;
    Army(*B2)+=x;
}
// memindahkan X buah pasukan dari bangunan B1 ke bangunan B2