/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#include "boolean.h"
#include "listlinier.h"
#include "stdio.h"
#include "stdlib.h"
/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong */
{
	return(First(L) == Nil);
}
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
	First(*L) = Nil;
}
/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	//Kamus Lokal
	address P;

	//Algo
	P = (address) malloc (sizeof (ElmtList));
	if (P != Nil) {
		Info(P) = X;
		Next(P) = Nil;
		return P;
	} else {
		return Nil;
	}
}
void Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(*P);
}
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	address P;
	boolean found = false;
	P = First(L);

	while((P!= Nil)&& (!(found))){
		if(Info(P) == X){
			found = true;
		} else{
			P = Next(P);
		}
	}
	return P;
}
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	//kamus
	address P;

	//Algo
	P = Alokasi(X);
	if (P != Nil) {
		InsertFirst(L, P);
	}
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	//kamus
	address P;

	//Algo
	P = Alokasi(X);
	if (P != Nil) {
		InsertLast(L, P);
	}
}
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	address P;
	P =First(*L);
	*X = Info(P);
	First(*L) = Next(First(*L));
	Next(P) = Nil;
	Dealokasi(&P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	address P;
	DelLast(L,&P);
	*X = Info(P);
	Dealokasi(&P);
}
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	Next(P) = First(*L);
	First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P) = Next(Prec);
	Next(Prec) = P;

}
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	address Pr;
	if(IsEmpty(*L)){
		InsertFirst(L,P);
	} else{
		Pr = First(*L);
		while(Next(Pr) != Nil){
			Pr =Next(Pr);
		}
		InsertAfter(L,P,Pr);
	}
}
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P =First(*L);
	First(*L) = Next(First(*L));
	Next(*P) = Nil;
}
void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	address P = Search(*L, X);

    if (P != Nil){   
        address prec = First(*L);

        if (prec == P){ 
            DelFirst(L, &P);
        }
        else {

            while(Next(prec) != P) { 
                prec = Next(prec);
            }

            DelAfter(L, &P, prec);
        }
    }
    Dealokasi(&P);

}
void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
	address Prec;
	*P = First(*L);
	Prec = Nil;
	
	while(Next(*P) != Nil){
		Prec = (*P);
		*P = Next(*P);
	}

	if(Prec == Nil){
		First(*L) = Nil;
	} else{
		Next(Prec) = Nil;
	}

}
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel =Next(Prec);
	Next(Prec) = Next(Next(Prec));
	Next(*Pdel) = Nil;
}
/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
	address P;
	
	printf("[");
	P = First(L);
	if (P != Nil) {
		printf("%d", Info(P));
	}
	P = Next(P);
	while (P != Nil) {
		printf(",");
		printf("%d", Info(P));
		P = Next(P);
	}
	printf("]");
}
int NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
	int count =0;
	address P = First(L);

	while(P != Nil){
		count++;
		P = Next(P);
	}
	return count;
}
/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
	address P,Max;
	P = First(L);
	Max = First(L);


	while(P != Nil){
		if(Info(Max) < Info(P)){
			Max = P;
		}
		P = Next(P);
	}
	return (Info(Max));
}
/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
	address P;
	CreateEmpty(L3);

	if(IsEmpty(*L1)){
		First(*L3) = First(*L2);
		CreateEmpty(L2);
	} else{
		First(*L3) = First(*L1);
		P = First(*L1);
		while(Next(P) != Nil){
			P = Next(P);
		}
		Next(P) = First(*L2);
		CreateEmpty(L1);
		CreateEmpty(L2);
	}
	
}


/*/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/

/*

address AdrMax (List L){

	address Max = First(L);
    address CP = First(L);

    while(CP != Nil){

        if (Info(CP) > Info(Max)){
            Max = CP;
        }

        CP = Next(CP);
    }

    return Max;
}

address AdrMin (List L){

	address Min = First(L);
    address CP = First(L);

    while(CP != Nil){

        if (Info(CP) < Info(Min)){
            Min = CP;
        }

        CP = Next(CP);
    }

    return Min;
}

infotype Max (List L)
/* Mengirimkan nilai Info(P) yang maksimum 
{
	return Info(AdrMax(L));
}

infotype Min (List L)
/* Mengirimkan nilai Info(P) yang maksimum 
{
	return Info(AdrMin(L));
}

float Average (List L)
/* Mengirimkan nilai rata rata Info(P) 
{
    int Count = 0;
    float Sum = 0;
    address CP = First(L);

    while(CP != Nil){

        Sum += Info(CP);
        Count++;
        CP = Next(CP);
    }

    return (Sum/Count);
}

/****************** PROSES TERHADAP LIST ******************
void Konkat1 (List *L1, List *L2, List *L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini *
{
    CreateEmpty(L3);

    if (!(IsEmpty(*L1))){
        First(*L3) = First(*L1);

        address last1 = First(*L1);

        while(Next(last1) != Nil) {
            last1 = Next(last1);
        }

        Next(last1) = First(*L2);
    }
    else{
        First(*L3) = First(*L2);
    }


    CreateEmpty(L1);
    CreateEmpty(L2);

}

/****************** PROSES TERHADAP LIST ******************
void DelAll (List *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi *
{
	infotype temp;

	while(!IsEmpty (*L)){
		DelVFirst(L, &temp);
	}

	CreateEmpty(L);
}

void InversList (List *L)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. *
{

	address P,Q;
	address temp;
	address First = First(*L);

	P = First(*L);
	Q = Next(P);

	while(Q != Nil){

		P = Q;
		Q = Next(Q);

		P;
		InsertFirst(L, P);
		Next(First) = Q;
	}
}

List FInversList (List L)
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus didealokasi *
{
	// Create temporary list
	List TempL;
	CreateEmpty(&TempL);

	// Create duplicate of original list
	List TempOrg;
	CreateEmpty(&TempOrg);
	TempOrg = FCopyList(L);

	infotype temp;
	address tempAdr;
	while(!IsEmpty(TempOrg)){

		DelVFirst(&TempOrg, &temp);
		tempAdr = Alokasi(temp);
		if (tempAdr != Nil) {
			InsertFirst(&TempL, tempAdr);
		}
		else{
			DelAll(&TempL);
			return TempL;
		}
	}

	return TempL;
}

void CopyList (List *L1, List *L2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen *
{
	First(*L2) = First(*L1);
}


List FCopyList (List L)
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus didealokasi *
{
	// Create temporary list
	List TempL;
	CreateEmpty(&TempL);

	address CP = First(L);
	address tempAdr;

	while(CP != Nil){

		tempAdr = Alokasi(Info(CP));
		if (tempAdr != Nil){
			InsertLast(&TempL, tempAdr);
			CP = Next(CP);
		}
		else{
			DelAll(&TempL);
			return TempL;
		}
	}

	return TempL;
}

void CpAlokList (List Lin, List *Lout)
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, didealokasi */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal *
{
	CreateEmpty(Lout);
	*Lout = FCopyList(Lin);
}

void Konkat (List L1, List L2, List * L3)
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-dealokasi dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi didealokasi *{
    CreateEmpty(L3);

	address tempAdr;
	infotype temp;
	address CP;
	boolean stop = false;

    if (!(IsEmpty(L1))){

        CP = First(L1);

        while ((CP != Nil) && (!stop)){

			temp = Info(CP);
			tempAdr = Alokasi(temp);
			if (tempAdr != Nil){
				InsertLast(L3, tempAdr);
				CP = Next(CP);
			}
			else {

				DelAll(L3);
				stop = true;
			}
		}

		CP = First(L2);

        while ((CP != Nil) && (!stop)){

			temp = Info(CP);
			tempAdr = Alokasi(temp);
			if (tempAdr != Nil){
				InsertLast(L3, tempAdr);
				CP = Next(CP);
			}
			else {

				DelAll(L3);
				stop = true;
			}
		}

    }
    else{

		CP = First(L2);

        while ((CP != Nil) && (!stop)){

			temp = Info(CP);
			tempAdr = Alokasi(temp);
			if (tempAdr != Nil){
				InsertLast(L3, tempAdr);
				CP = Next(CP);
			}
			else {

				DelAll(L3);
				stop = true;
			}
		}
    }
}

void PecahList (List *L1, List *L2, List L)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 *
{
	int repeat = NbElmt(L) / 2;
	int repeatII = NbElmt(L) - repeat;
	address tempAdr;
	infotype temp;
	address CP = First(L);

	CreateEmpty(L1);
	CreateEmpty(L2);

	while(repeat > 0){

		temp = Info(CP);
		tempAdr = Alokasi(temp);
		if (tempAdr != Nil){
			InsertLast(L1, tempAdr);
			CP = Next(CP);
			repeat--;
		}

	}

	while(repeatII > 0){

		temp = Info(CP);
		tempAdr = Alokasi(temp);
		if (tempAdr != Nil){
			InsertLast(L2, tempAdr);
			CP = Next(CP);
			repeatII--;
		}
	}
}*/