#include "ListaArray.h"
#include "ListaLinkada.h"
#include <stdio.h>
#include <stdlib.h>

/*tudo OK, até o dia 20/11/2023*/

//===================================================================

typedef struct arrayList{
    SemSinal maxSize;
    SemSinal ArrayListSize;
    SemSinal curr;
    E* ArrayListArray;
} ArrayList;

//------------------------------------------------------------------

ArrayList* create_ArrayList(int size){
    ArrayList* l = (ArrayList*) malloc(sizeof(ArrayList));
    l->maxSize = size;
    l->ArrayListSize = l->curr = 0;
    l->ArrayListArray = (E*) malloc(size * sizeof(E));
    return l;
}

//------------------------------------------------------------------

void insertArrayList(ArrayList* l, E item){
    if(l->ArrayListSize < l->maxSize){
        SemSinal i = l->ArrayListSize;
        while (i > l->curr){
            l->ArrayListArray[i] = l->ArrayListArray[i-1];
            i--;
        }
        l->ArrayListArray[l->curr] = item;
        l->ArrayListSize++;
    }
    else{
        printf("Nao eh possivel isso\n");
    }
}
void clearArrayList(ArrayList* l){
    free(l->ArrayListArray);
    l->ArrayListArray=NULL;
    free(l);
    l = NULL;
}
void appendArrayList(ArrayList* l, E item){
    if(l->ArrayListSize < l->maxSize){
        l->ArrayListArray[l->ArrayListSize] = item;
        l->ArrayListSize++;
    }
    else printf("The ArrayList is full\n");
}
E removeArrayList(ArrayList* l){
    if(l->curr < 0 || l->curr >= l->ArrayListSize) { 
        printf("Nao eh possivel\n");
        return -1; 
    }
    E item = l->ArrayListArray[l->curr]; 
    SemSinal i = l->curr;
    while(i<l->ArrayListSize-1){
        l->ArrayListArray[i] = l->ArrayListArray[i+1];
        i++;
    }
    l->ArrayListSize--;
    return item;
}

//------------------------------------------------------------------

void moveToStartArrayList(ArrayList* l){
    l->curr = 0;
}
void moveToEndArrayList(ArrayList* l){
    l->curr = l->ArrayListSize;
}
void prevArrayList(ArrayList* l){
    if(l->curr > 0 && l->curr >=l->ArrayListSize) l->curr--;
}
void nextArrayList(ArrayList* l){
    if(l->curr < l->ArrayListSize) l->curr++;
}

//------------------------------------------------------------------

SemSinal lengthArrayList(ArrayList* l){
    return l->ArrayListSize;
}
SemSinal currPosArrayList(ArrayList* l){
    return l->curr;
}
void moveToPosArrayList(ArrayList* l, SemSinal pos){
    if(pos < l->maxSize) l->curr = pos;
}
E getValueArrayList(ArrayList* l){
    return l->ArrayListArray[l->curr];
}

//------------------------------------------------------------------

//uteis
void usarArrayListaNormal(){
    FILE* arquivo = fopen("EntradasDaMainArrayLista.txt", "at");
    fprintf(arquivo,"%s\n", "Uma Nova Combinação da ArrayLista Normal: ");

    int size; scanf("%d", &size);
    ArrayList* l = create_ArrayList(size);
    int escolha=-1;
    SemSinal atual, tam; E item, elemento; //nao pode declarar variaveis entre os cases do switch case

    printf("1.Limpar\n2.Inserir\n3.Remover\n4.MoverProInicio\n5.MoverProFinal\n6.Anteceder\n7.Proceder\n8.IndiceAtual\n9.ElementosTotais\n10.ValorAtual\n11.PrintarArrayLista\n12.AdcionarNoFinal\n\n");
    
    do{
        printf("Escolha: ");scanf("%d", &escolha);
        fprintf(arquivo, "%d-", escolha);
        switch(escolha){
            case 1:
                clearArrayList(l);
                l = create_ArrayList(size);
                break;
            case 2:
                printf("Digite um elemento: "); 
                scanf("%f", &item);
                insertArrayList(l, item);
                break;
            case 3:
                removeArrayList(l);
                break;
            case 4:
                moveToStartArrayList(l);
                break;
            case 5:
                moveToEndArrayList(l);
                break;
            case 6:
                prevArrayList(l);
                break;
            case 7:
                nextArrayList(l);
                break;
            case 8:
                atual = currPosArrayList(l);
                printf("Cursor: %d\n", atual);
                break;
            case 9:
                tam = lengthArrayList(l);
                printf("Tamanho: %d\n", tam);
                break;
            case 10:
                elemento = getValueArrayList(l);
                printf("Elemento: %f\n", elemento);
                break;
            case 11:
                printArrayLista(l);
                break;
            case 12:
                printf("Digite um elemento: "); 
                scanf("%f", &item);
                appendArrayList(l, item);
                break;
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }while(escolha!=1);
    
    fprintf(arquivo, "\n");

    fclose(arquivo);
    clearArrayList(l);
}
void printArrayLista(ArrayList* l){
    printf("ArrayLista Interia\n");
    printf("<");
    for(SemSinal i=0; i<l->ArrayListSize; i++){
        if(i != l->ArrayListSize -1)
            printf("%.2f,", l->ArrayListArray[i]);
        else
            printf("%.2f>", l->ArrayListArray[i]);
    }
    printf("\n");
}

//===================================================================

typedef struct node{
    E element;
    Node* next;
}Node;

//------------------------------------------------------------------

typedef struct list{
    Node* head;
    Node* tail;
    Node* curr;
    SemSinal cnt;
} List;

//------------------------------------------------------------------

Node* createFirst_node(Node* nextval){
    Node* n = (Node*) malloc(sizeof(Node));
    n->next = nextval;
    return n;
}
Node* create_node(E it, Node* nextval){
    Node* n = (Node*) malloc(sizeof(Node)); 
    n->element = it;
    n->next = nextval;
    return n;
}
List* create_LinkedList(){
    List* l = (List*) malloc(sizeof(Node));
    l->curr = l->tail = l->head = createFirst_node(NULL);
    l->cnt = 0;
    return l;
}
void removeAll(List* l){
    clearLinkedList(l);
    free(l->head);
    free(l);
}

//------------------------------------------------------------------

void clearLinkedList(List* l){
    moveToStartLinkedList(l);
    Node* tempNext = l->head->next;
    while(tempNext != NULL){
        Node* removed = tempNext;
        tempNext = tempNext->next;
        free(tempNext);
    }
    free(l->tail);
    free(l->curr);
    free(l->head);
    free(l);
    l = create_LinkedList();
}
void insertLinkedList(List* l, E item){
    Node* temp = create_node(item, l->curr->next);
    l->curr->next = temp;
    if(l->tail == l->curr) l->tail = l->curr->next;
    l->cnt++;
    
}
void appendLinkedList(List* l, E item){
    Node* n = create_node(item, NULL);
    l->tail->next = n;
    l->tail = n;
    l->cnt++;
}
E removeLinkedList(List* l){
    if(l->curr->next == NULL) { 
        printf("It is not possible hahaha\n"); 
        return (E)-1; 
    }
    E removed = l->curr->next->element;
    Node* temp = l->curr->next;

    if(l->tail == l->curr->next) l->tail = l->curr;
    l->curr->next = l->curr->next->next; 
    free(temp);
    l->cnt--;
    return removed;
}

//------------------------------------------------------------------

void moveToStartLinkedList(List* l){
    l->curr = l->head;
}
void moveToEndLinkedList(List* l){
    l->curr = l->tail;
}
void prevLinkedList(List* l){
    if(l->curr == l->head) return;
    Node* temp = l->head;
    while(temp->next != l->curr)
        temp = temp->next;
    l->curr = temp;
}
void nextLinkedList(List* l){
    if(l->curr != l->tail) l->curr = l->curr->next;
}

//------------------------------------------------------------------

SemSinal lengthLinkedList(List* l){
    return l->cnt;
}
SemSinal currPosLinkedList(List* l){
    Node* temp = l->head;
    SemSinal i = 0;
    while(temp != l->curr){
        temp = temp->next;
        i++;
    }
    return i;
}
void moveToPosLinkedList(List* l, SemSinal pos){
    if(pos>0 && pos<l->cnt) {
        Node* temp = l->head;
        int i=0;
        while(i != pos && temp != NULL){
            temp = temp->next;
            i++;
        }
        l->curr = temp;
    }
    else {
        printf("This is out of range\n");
    }
} /*n sei se funciona*/
E getValueLinkedList(List* l){
    if(l->curr->next != NULL)
        return l->curr->next->element;
    return (E)-1;
}

//------------------------------------------------------------------

//uteis
void usarListaLinkada(){
    FILE* arquivo = fopen("EntradasDaMainLista.txt", "at");
    fprintf(arquivo, "%s\n", "Uma Nova Combinação da Lista Linkada: ");

    List* l = create_LinkedList();
    int escolha=-1;
    SemSinal atual, tam; E item, elemento; //nao pode declarar variaveis entre os cases do switch case

    printf("1.Limpar\n2.Inserir\n3.Remover\n4.MoverProInicio\n5.MoverProFinal\n6.Anteceder\n7.Proceder\n8.IndiceAtual\n9.ElementosTotais\n10.ValorAtual\n11.PrintarLista\n12.AdcionarNoFinal\n\n");
    
    do{
        printf("Escolha: ");scanf("%d", &escolha);
        fprintf(arquivo, "%d-", escolha);
        switch(escolha){
            case 1:
                clearLinkedList(l);
                l = create_LinkedList();
                break;
            case 2:
                printf("Digite um elemento: "); 
                scanf("%f", &item);
                insertLinkedList(l, item);
                break;
            case 3:
                removeLinkedList(l);
                break;
            case 4:
                moveToStartLinkedList(l);
                break;
            case 5:
                moveToEndLinkedList(l);
                break;
            case 6:
                prevLinkedList(l);
                break;
            case 7:
                nextLinkedList(l);
                break;
            case 8:
                atual = currPosLinkedList(l);
                printf("Cursor: %d\n", atual);
                break;
            case 9:
                tam = lengthLinkedList(l);
                printf("Tamanho: %d\n", tam);
                break;
            case 10:
                elemento = getValueLinkedList(l);
                printf("Elemento: %f\n", elemento);
                break;
            case 11:
                printLinkedList(l);
                break;
            case 12:
                printf("Digite um elemento: "); 
                scanf("%f", &item);
                appendLinkedList(l, item);
                break;
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }while(escolha!=1);
    
    fprintf(arquivo, "\n");

    clearLinkedList(l);
    fclose(arquivo);
}
void printLinkedList(List* l){
    printf("Lista Inteira\n");
    printf("<");
    for(moveToStartLinkedList(l); l->curr != l->tail; nextLinkedList(l)){
        printf("%.2f, ", l->curr->element);
    }
    printf(">\n");
}

//===================================================================