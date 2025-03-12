#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//usei a Deepseek inicialmente
//otimizei o que foi possível

typedef struct coisa{
    bool tem_espaco;
    bool eh_numerico;
    bool eh_alfa;
    bool eh_alnum;
    bool eh_maiusculo;
    bool eh_minusculo;
    bool eh_titulo;
} coisa;

void what_is_this(const char *str, coisa* algo) {
    if (*str == '\0') return;
    //verdade ate q se prove o contrario
    bool espaco = true;
    bool numero = true;
    bool alfa = true;
    bool alfanum = true;
    bool titulo = true;
    //maiusculo
    int has_cased = 0;
    int all_upper = 1;
    //minusculo
    int has_cased_low = 0;
    int all_lower = 1;
    //titulo
    int in_word = 0;
    int first_cased_found = 0;
    int has_cased_title = 0;
    //loop
    for (const char *p = str; *p != '\0'; p++) {
        //eh espaço //era pra ser "tem espaço"
        if (espaco && !isspace((unsigned char)*p)) {
            espaco = false;
        }
        //eh numero
        if (numero && !isdigit((unsigned char)*p)) {
            numero = false;
        }
        //eh letras
        if (alfa && !isalpha((unsigned char)*p)) {
            alfa = false;
        }

        //eh numero ou letra
        if (alfanum && !isalnum((unsigned char)*p)) {
            alfanum = false;
        }
        
        //eh todo maiusculo
        if (isalpha((unsigned char)*p)) {
            has_cased = 1;
            if (islower((unsigned char)*p)) {
                all_upper = 0;
            }
        }
        //eh todo minusculo
        if (isalpha((unsigned char)*p)) {
            has_cased_low = 1;
            if (isupper((unsigned char)*p)) {
                all_lower = 0;
            }
        }
        //eh um titulo
        unsigned char c = *p;
        if (isspace(c)) {
            in_word = 0;
            first_cased_found = 0;
        } else {
            if (!in_word) {
                in_word = 1;
                first_cased_found = 0;
            }
            if (isalpha(c)) {
                has_cased_title = 1;
                if (!first_cased_found) {
                    if (islower(c)) {
                        titulo = false;
                    }
                    first_cased_found = 1;
                } else {
                    if (isupper(c)) {
                        titulo = false;
                    }
                }
            }
        }
    }
    //outros
    algo->tem_espaco = espaco;
    algo->eh_numerico = numero;
    algo->eh_alfa = alfa;
    algo->eh_alnum = alfanum;
    //maiusculo
    algo->eh_maiusculo = has_cased && all_upper;
    //minusculo
    algo->eh_minusculo = has_cased_low && all_lower;
    //titulo
    algo->eh_titulo = titulo && has_cased_title;
    return;
}

void what_type_is_this(char *tipo, coisa algo){
    if(algo.eh_numerico){
        strcpy(tipo, "int\0");
    }
    else{
        strcpy(tipo, "char\0");
    }
}

int main() {
    char entrada[100];
    coisa algo;
    printf("Digite algo: ");
    fgets(entrada, sizeof(entrada), stdin);

    // Remove a quebra de linha do final da string
    size_t len = strlen(entrada);
    if (len > 0 && entrada[len - 1] == '\n') {
        entrada[len - 1] = '\0';
    }

    what_is_this(entrada, &algo);
    char tipo[5];
    what_type_is_this(tipo, algo);
    

    printf("O tipo primitivo desse valor eh: %s\n", tipo);
    printf("Soh tem espacos? %s\n", algo.tem_espaco ? "Sim" : "Nao");
    printf("Eh um numero? %s\n", algo.eh_numerico ? "Sim" : "Nao");
    printf("Eh alfabetico? %s\n", algo.eh_alfa ? "Sim" : "Nao");
    printf("Eh alfanumerico? %s\n", algo.eh_alnum ? "Sim" : "Nao");
    printf("Estah em maiusculas? %s\n", algo.eh_maiusculo ? "Sim" : "Nao");
    printf("Estah em minusculas? %s\n", algo.eh_minusculo ? "Sim" : "Nao");
    printf("Estah capitalizada? %s\n", algo.eh_titulo ? "Sim" : "Nao");

    return 0;
}