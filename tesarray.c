#include "arraydin.h"
#include "bangunan.h"
#include <stdio.h>

int main(){
    Bangunan B;
    TabInt T;
    MakeEmptyAB(&T,5);
    CreateBangunan (&B, 'C', 1, 2);
    T.TI[0]=B;
    CreateBangunan (&B, 'T', 2, 3);
    T.TI[1]=B;
    CreateBangunan (&B, 'V', 3, 4);
    T.TI[2]=B;
    CreateBangunan (&B, 'F', 4, 1);
    T.TI[3]=B;
    CreateBangunan (&B, 'C', 3, 2);
    T.TI[4]=B;
    for(int i=0; i<5; i++){
        printf("%d. ",i+1);
        CetakBangunan(T.TI[i]);
    }
}