#ifndef LIST_H
#define LIST_H


#include "Item.h"

typedef struct node* Link; 

Link listInsert(Link l, Item i);

Item listExtractElem(Link* lp, Key k);
Item listSearchElem(Link l, Key k);
Link listExtractSeq(Link* l, char* dateS, char* dateF);

void listPrint(Link l);

#endif
