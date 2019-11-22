#include "listlinier.h"
#include <stdio.h>

int main(){
    List L;
    CreateEmptyLB(&L);
    for(int i=0; i<5; i++) InsVLastLB(&L,i+1);
    printf("Jumlah elemen: %d\n",NbElmtLB(L));
    address P;
    P=First(L);
    while(P!=Nil){
        printf("Isi: %d\n",Info(P));
        P=Next(P);
    }
}