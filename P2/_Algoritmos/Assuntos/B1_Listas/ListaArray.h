#ifndef _LIST_H
#define _LIST_H

/*tudo OK, até o dia 20/11*/

typedef struct list List;
typedef float E; typedef unsigned int SemSinal;


List* create_list(int size);

void insertList(List* l, E item);
void clearList(List* l);
void appendList(List* l, E item);
E removeList(List* l);

void moveToStartList(List* l);
void moveToEndList(List* l);
void prevList(List* l);
void nextList(List* l);

SemSinal lengthList(List* l);
SemSinal currPosList(List* l);
void moveToPosList(List* l, SemSinal pos);
E getValueList(List* l);

//uteis
void usarListaNormal();
void printLista(List* l);

#endif