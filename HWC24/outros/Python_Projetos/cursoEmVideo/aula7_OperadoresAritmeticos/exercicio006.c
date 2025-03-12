#include <stdio.h>
#include <math.h>

int main(){
    int entrada;
    printf("Digite um numero: ");
    scanf("%d", &entrada);
    printf("O dobro de %d vale %d.\nO triplo de %d vale %d.\n", entrada, entrada*2, entrada, entrada*3);
    printf("A raiz quadrada de %d eh %.2f", entrada, sqrt((double)entrada));
}
