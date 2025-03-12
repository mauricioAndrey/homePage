#include <stdio.h>

int main(){
    float entrada = 0; 
    printf("Uma distancia em metros: ");
    scanf("%f", &entrada);

    printf("A medida de %.1fm corresponde a \
            \n%.4fkm\n%.3fhm\n%.2fdam\n%.1fdm\n%.1fcm\n%.1fmm\n"\
            , entrada, entrada/1000, entrada/100, entrada/10,\
            entrada*10, entrada*100, entrada*1000);
}