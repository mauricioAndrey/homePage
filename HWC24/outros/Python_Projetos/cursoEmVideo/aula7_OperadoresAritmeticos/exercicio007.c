#include <stdio.h>

int main(){
    float nota1,nota2;
    printf("Primeira nota do aluno: ");
    scanf("%f", &nota1);
    printf("Segunda nota do aluno: ");
    scanf("%f", &nota2);

    printf("A media entre %.1f e %.1f eh igual a %.1f", nota1, nota2, (nota1+nota2)/2);
    
}