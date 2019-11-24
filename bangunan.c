#include <stdio.h>
#include "bangunan.h"

int GetA(Bangunan B){
// mereturn nilai penambahan pasukan / A dari Bangunan B sesuai dengan levelnya
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
// mereturn nilai Maksimum penambahan pasukan dari Bangunan B sesuai dengan levelnya
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
// mereturn ada atau tidaknya pertahanan dari Bangunan B sesuai dengan levelnya
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
// aksi : menginisialisasi type, point, level, dan pasukan pada bangunan B
// I.S. bangunan belum di inisialisasi
// F.s. terbentuk bangunan
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
// menaikan level suatu bangunan dengan syarat pasukannya 
// sudah lebih dari setengah M bangunan tsb
// I.S. bangunan terdefinisi
// F.s bangunan naik level, dan pasukannya berkurang

	if(Army(*B) >= 0.5 * GetM(*B)){
		Army(*B)-=(0.5 * GetM(*B));
		Level(*B)+=1;
	}
	else printf("Anda tidak bisa level up\n");
}

boolean CekBatasPasukan(Bangunan B){
	// Cek apakah nilai dari penambahan pasukan melebihi M
	// jika sudah melebihi, stop penambahan
	return (Army(B)+GetA(B) <= GetM(B));
}

void AddPasukan(Bangunan *B){
// menambahkan A jumlah pasukan ke bangunan dengan syarat
// bangunan sudah berkepemilikan
// I.S. bangunan terdefinisi
// F.S pasukan pada bangunan bertambah sebanyak A pada setiap turn
	if(CekBatasPasukan(*B) && Owner(*B)!=0){
		Army(*B)+=GetA(*B);
	}else if(CekBatasPasukan(*B)==false && Owner(*B)!=0){
		Army(*B) = GetM(*B);
	}
}

void ChangeOwnerB(Bangunan *B, int X, int Y){
// reset bangunan saat pindah kepemilikan, 
// dengan X sebagai jumlah pasukan yang baru
// dan Y sebagai pemilik yang baru
// I.S. bangunan terdefinisi
// F.S. pemilik B berubah dari X menjadi Y
    Level(*B) = 1;
    Army(*B) = X;
    Owner(*B) = Y;
}

void MovePasukan(Bangunan *B1, Bangunan *B2, int x){
// memindahkan X buah pasukan dari bangunan B1 ke bangunan B2
// I.S. 2 Bangunan terdefinsi
// F.S. pasukan B1 berkurang sebanyak x dan pasukan B2 bertambah sebanyak y
	Army(*B1)-=x;
    Army(*B2)+=x;
}

void CetakBangunan(Bangunan B){
// mencetak bagunan dengan format:
// <no> <tipe bangunan> <(point)> <pasukan> <level>
// I.S. bangunan terdefinisi
// F.S tercetak isi bangunan B
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