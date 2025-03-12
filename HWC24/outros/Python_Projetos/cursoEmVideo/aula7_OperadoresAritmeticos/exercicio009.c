#include <stdio.h>

int main(){
    int numero;
    printf("Digite um numero da sua tabuada: ");
    scanf("%d", &numero);
    
    printf("---------------\n");
    for(int i=1; i<11; i++){
        printf("%d x %d = %d\n", numero, i, numero*i);
    }
    printf("---------------");
}