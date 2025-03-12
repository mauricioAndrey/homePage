#include <stdio.h>

int main(){
    float real;
    printf("Quanto dinheiro voce tem na carteira? R$");
    scanf("%f", &real);
    float dolar = real/5.8;
    printf("Com R$%.2f voce pode comprar US$%.2f", real, dolar);
}