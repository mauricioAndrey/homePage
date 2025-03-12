#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main(){
    char entrada[100];
    printf("Digite um numero: ");
    fgets(entrada, sizeof(entrada), stdin);

    // Remove a quebra de linha do final da string
    size_t len = strlen(entrada);
    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
    }

    //verificando se eh numero
    bool eh_numero = true;
    for(char *p = entrada; eh_numero && *p!= '\0'; p++){
        if(!isdigit((unsigned char)*p))
            eh_numero = false;
    }

    if(eh_numero){
        int numero = atoi(entrada);
        printf("O antecessor de %d eh %d e o sucessor eh %d\n", numero, numero-1, numero+1);
    } else {
        printf("Isso nem eh numero\n");
    }
    
}