#include "stackt.h"
#include <stdio.h>

int main(){
    Stack st;
    state isi;
    CreateEmptyStack(&st);
    int n;
    char c;
    isi.M.NBrsEff =3;
    printf("%d adalah tinggi peta sekarang.\n",isi.M.NBrsEff);
    PushStack(&st,isi);
    scanf("%d",&n);
    isi.M.NBrsEff += n;
    printf("%d telah ditambahkan sehingga tinggi peta menjadi %d\n",n,isi.M.NBrsEff);
    PopStack(&st,&isi);
    printf("input apapun untuk undo");scanf(" %c",&c);
    printf("setelah di undo tinggi peta kembali menjadi %d\n",isi.M.NBrsEff);
}