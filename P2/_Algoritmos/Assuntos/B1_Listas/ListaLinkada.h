#ifndef _LISTLINKED_H
#define _LISTLINKED_H

typedef struct node Node;
typedef struct list List;
typedef float E; typedef unsigned int SemSinal;

Node* createFirst_node(Node* nextval);
Node* create_node(E it, Node* nextval);
List* create_LinkedList();
void removeAll();

void insertLinkedList(List* l, E item);
void clearLinkedList(List* l);
void appendLinkedList(List* l, E item);
E removeLinkedList(List* l);

void moveToStartLinkedList(List* l);
void moveToEndLinkedList(List* l);
void prevLinkedList(List* l);
void nextLinkedList(List* l);

SemSinal lengthLinkedList(List* l);
SemSinal currPosLinkedList(List* l);
void moveToPosLinkedList(List* l, SemSinal pos);
E getValueLinkedList(List* l);

//uteis
void usarListaLinkada();
void printLinkedList(List* l);


#endif