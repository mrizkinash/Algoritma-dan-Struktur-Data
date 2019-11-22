/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
#include "boolean.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
	return(Tail(Q) ==0 && Head(Q) == 0);
}
boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQueue */
{
	return(Tail(Q) == MaxElQueue(Q));
}
int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if (IsEmptyQueue(Q)) {
		return Nol;
	} else if (Head(Q) <= Tail(Q)){
		return (Tail(Q)-Head(Q)+1);
	} else {
		return (MaxElQueue(Q) - Head(Q) + Tail(Q) + 1);
	}
}
/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQueue=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (infotype *) malloc ((Max+1) * sizeof(infotype));
	if((*Q).T != NULL){
		Head(*Q) = Nol;
		Tail(*Q) = Nol;
		MaxElQueue(*Q) = Max;
	} else {
		(*Q).MaxElQueue = 0;
	}

}
/* *** Destruktor *** */
void DeAlokasiQueue (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) diset 0 */
{
	free((*Q).T);
	MaxElQueue(*Q) =Nol;
}
/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	if(IsEmptyQueue(*Q)){
		Head(*Q) =1;
		Tail(*Q) =1;
		InfoHead(*Q) = X; 
	} else {
		if(IsFullQueue(*Q)){
			Tail(*Q) =1;
			InfoTail(*Q) =X;
		} else {
			Tail(*Q)++;
			InfoTail(*Q) =X;
		}
	}
}
void DelQueue (Queue * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
	*X = InfoHead(*Q);
    if(Head(*Q)==Tail(*Q)){
        Head(*Q) = Nol;
        Tail(*Q) = Nol;
    }
    else{
        Head(*Q) = Head(*Q) + 1;
    }
}

void PrintQueue(Queue Q){
	adrQ P;

	if(IsEmptyQueue(Q)){
		printf("\n");
	}
	else{
		while (Head(Q) < Tail(Q)){
			printf("%d ", InfoHead(Q));
			Head(Q)++;
		}
		// Head(Q) = Tail(Q)
		printf("%d\n", InfoHead(Q));
		Head(Q) = P;
	}
}

void PrintSkill(Queue Q){
    if(IsEmptyQueue(Q)){
        printf("Anda tidak memiliki skill yang dapat digunakan!\n");
    }else{
        if(InfoHead(Q) == 1){
            printf("Instant Upgrade\n");
        }else if(InfoHead(Q) == 2){
            printf("Extra Turn\n");
        }else if(InfoHead(Q) == 3){
            printf("Instant Reinforcement\n");
        }else if(InfoHead(Q) == 4){
            printf("Barrage\n");
        }
    }
}

// void UseSkill(state *S){
//     int InfoSkill;
// 	Player cek;
// 	if(S->P1.turn) cek=S->P1;
// 	else cek=S->P2;
//     InfoSkill = InfoHead(cek.skill);
//     if (InfoSkill == 1){
//         instantUpgrade(S);
//     }else if (InfoSkill == 3){
//         instantReinforcement(S);
//     }else if (InfoSkill == 4){
//         Barrage(S);
//     }else if (InfoSkill == 2){
//         extraTurn(S);
//     }
//     DelQueue(&(cek.skill), &InfoSkill);
// }

// void instantUpgrade(state *S){
//     // seluruh bangunan yg dimiliki player levelnya naik 1
// 	Player cek;
// 	if(S->P1.turn) cek=S->P1;
// 	else cek=S->P2;
//     address adr = First(cek.listbangunan);
//     while(adr != Nil){
//         LevelUpBangunan(&(S->ArrBang.TI[Info(adr)]));
//         adr = Next(adr);
//     }
//     printf("skill 'Instant Upgrade' berhasil dilakukan!\n");
// }

// void instantReinforcement(state *S){
//     // seluruh bangunan +5 army
// 	Player cek;
// 	if(S->P1.turn) cek=S->P1;
// 	else cek=S->P2;
//     address adr;
//     adr = First(cek.listbangunan);
//     while(adr != Nil){
//         Army(S->ArrBang.TI[Info(adr)]) += 5;
//         adr = Next(adr);
//     }
//     printf("skill 'Instant Reinforcement' berhasil dilakukan!\n");
// }

// void Barrage(state *S){
//     // iterasi buat semua bangunan lawan di -10 army
// 	Player cek;
// 	if(S->P1.turn) cek=S->P1;
// 	else cek=S->P2;
//     address adr;
//     adr = First(cek.listbangunan);
//     while(adr != Nil){
//         if (Army(S->ArrBang.TI[Info(adr)]) >= 10){
//             Army(S->ArrBang.TI[Info(adr)]) -= 10;
//         }else{
//             Army(S->ArrBang.TI[Info(adr)]) = 0;
//         }
//         adr = Next(adr);
//     }
    
//     printf("skill 'Barrage' berhasil dilakukan!\n");
// }

// void extraTurn(state *S){
// 	Player cek;
// 	if(S->P1.turn) cek=S->P1;
// 	else cek=S->P2;
// 	cek.et=true;
// }