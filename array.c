/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel statik */

	 #include "boolean.h"
	 #include "array.h"
	 #include "stdio.h"
/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyArray (TabInt * T){
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
	Neff(*T) = 0;
}
/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtArray (TabInt T){
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
	return(Neff(T));
}
int MaxNbElArray (TabInt T){
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
	return (100);
}
IdxType GetFirstIdxArray (TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
	return (IdxMin);
}
IdxType GetLastIdxArray (TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
	return(Neff(T));
}
/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidArray (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
	return ((1 <= i) && (i <= 100));
}
boolean IsIdxEffArray (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
	return ((IdxMin <= i) && (i <= Neff(T)));
}
/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyArray (TabInt T){
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
	return (Neff(T) == 0);
}
boolean IsFull (TabInt T){
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
	return (Neff(T) == IdxMax);
}
/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsiArray (TabInt * T){
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
	int i,N;

	do {
		scanf("%d", &N);
	} while((N < 0) || (N > IdxMax));

	Neff(*T) = N;
	for (i=1; i<=N; i++) {
		scanf("%d", &Elmt(*T,i));
	}
}
void BacaIsiTabArray (TabInt * T){
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca elemen T sampai dimasukkan nilai -9999 */
/* Dibaca elemen satu per satu dan disimpan mulai dari IdxMin */
/* Pembacaan dihentikan jika pengguna memasukkan nilai -9999 */
/* Jika dari pertama dimasukkan nilai -9999 maka terbentuk T kosong */
	int x,i;

	i = 1;
	scanf("%d", &x);
	while ((x != -9999) && (i<=100)) {
		Elmt(*T,i) = x;
		scanf("%d", &x);
		i++;
	}
	Neff(*T) = i-1;
}
void TulisIsiArray (TabInt T){
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
  int i;

	if (T.Neff == 0) {
		printf("Tabel kosong\n");
	}
	for (i=1; i<=T.Neff; i++) {
		printf("["); printf("%d",i); printf("]"); printf("%d\n", Elmt(T,i));
	}
}
void TulisIsiTabArray (TabInt T){
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
	int i;

	printf("[");
	for (i=1; i<=T.Neff; i++) {
		printf("%d", Elmt(T,i));
		if (i != T.Neff) {
			printf(",");
		}
	}
	printf("]");
}
