#include <stdio.h>
#include "bangunan.h"

int GetA(Bangunan B){
	//CASTLE
	if(Type(B)=='C' && Level(B)==1) return 10;
	else if(Type(B)=='C' && Level(B)==2) return 15;
	else if(Type(B)=='C' && Level(B)==3) return 20;
	else if(Type(B)=='C' && Level(B)==4) return 25;
	//TOWER
	else if(Type(B)=='T' && Level(B)==1) return 5;
	else if(Type(B)=='T' && Level(B)==2) return 10;
	else if(Type(B)=='T' && Level(B)==3) return 20;
	else if(Type(B)=='T' && Level(B)==4) return 30;
	//FORT
	else if(Type(B)=='F' && Level(B)==1) return 10;
	else if(Type(B)=='F' && Level(B)==2) return 20;
	else if(Type(B)=='F' && Level(B)==3) return 30;
	else if(Type(B)=='F' && Level(B)==4) return 40;
	//VILLAGE
	else if(Type(B)=='V' && Level(B)==1) return 5;
	else if(Type(B)=='V' && Level(B)==2) return 10;
	else if(Type(B)=='V' && Level(B)==3) return 15;
	else if(Type(B)=='V' && Level(B)==4) return 20;
}

int GetM(Bangunan B){
	//CASTLE
	if(Type(B)=='C' && Level(B)==1) return 40;
	else if(Type(B)=='C' && Level(B)==2) return 60;
	else if(Type(B)=='C' && Level(B)==3) return 80;
	else if(Type(B)=='C' && Level(B)==4) return 100;
	//TOWER
	else if(Type(B)=='T' && Level(B)==1) return 20;
	else if(Type(B)=='T' && Level(B)==2) return 30;
	else if(Type(B)=='T' && Level(B)==3) return 40;
	else if(Type(B)=='T' && Level(B)==4) return 50;
	//FORT
	else if(Type(B)=='F' && Level(B)==1) return 20;
	else if(Type(B)=='F' && Level(B)==2) return 40;
	else if(Type(B)=='F' && Level(B)==3) return 60;
	else if(Type(B)=='F' && Level(B)==4) return 80;
	//VILLAGE
	else if(Type(B)=='V' && Level(B)==1) return 20;
	else if(Type(B)=='V' && Level(B)==2) return 30;
	else if(Type(B)=='V' && Level(B)==3) return 40;
	else if(Type(B)=='V' && Level(B)==4) return 50;
}

boolean GetP(Bangunan B){
	//CASTLE
	if(Type(B)=='C') return false;
	//TOWER
	else if(Type(B)=='T') return true;
	//FORT
	else if(Type(B)=='F' && Level(B)==1) return false;
	else if(Type(B)=='F' && Level(B)==2) return false;
	else if(Type(B)=='F' && Level(B)==3) return true;
	else if(Type(B)=='F' && Level(B)==4) return true;
	//VILLAGE
	else if(Type(B)=='V') return false;
}

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
	if(Army(*B) >= 0.5 * GetM(*B)){
		Army(*B)-=(0.5 * GetM(*B));
		Level(*B)+=1;
	}
	else printf("Anda tidak bisa level up\n");
}
// level +=1
// jumlah pasukan berkurang M/2

boolean CekBatasPasukan(Bangunan B){
	return (Army(B)+GetA(B) <= GetM(B));
}
// Cek apakah nilai dari penambahan pasukan melebihi M
// jika sudah melebihi, stop penambahan

void AddPasukan(Bangunan *B){
	if(CekBatasPasukan(*B) && Owner(*B)!=0){
		Army(*B)+=GetA(*B);
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

void CetakBangunan(Bangunan B){
	if(Type(B)=='C') printf("Castle ");
	else if(Type(B)=='T') printf("Tower ");
	else if(Type(B)=='F') printf("Fort ");
	else if(Type(B)=='V') printf("Village ");
	int x = AbsisBangunan(B);
	int y = OrdinatBangunan(B);
	printf("(%d,%d) ",x,y);
	printf("%d ",Army(B));
	printf("lv. %d\n",Level(B));
}