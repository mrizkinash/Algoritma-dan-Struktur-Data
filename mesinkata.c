/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "mesinkata.h"
#include "boolean.h"
#include "mesinkar.h"

boolean EndKata;
Kata CKata;
char CC;
//boolean EOP;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    while(((CC == BLANK) || (CC == '\n')) && (CC !='.')){
        ADV();
    }
}
void STARTKATA()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    START();
    IgnoreBlank();

    if(CC == '.'){
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
        IgnoreBlank();
    }
}
void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    if(CC == '.'){
        EndKata =true;
    } else{
        SalinKata();
        IgnoreBlank();
        if(CC == '.'){
            EndKata =true;
        }
    }
}
void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i;
    i=1;
    do{
        CKata.TabKata[i]=CC; 
        ADV();
        i++;
    } while(((CC != BLANK) && (CC != '.')) && (i<=NMax) && (CC != '\n'));
    CKata.Length = i-1;
}   

void STARTKATACMD()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    STARTCMD();
    IgnoreBlank();

    if(CC == '.'){
        EndKata = true;
    } else {
        EndKata = false;
        SalinKata();
        IgnoreBlank();
    }
}