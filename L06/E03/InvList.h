#ifndef INVLIST_H
#define INVLIST_H

#include "Inventario.h"
#include <string.h>

typedef struct InvList{
 	Inv* vettInv;
	int nInv;
	int maxInv;

} InvList;

int invList_find(InvList invList, char* nome);
Inv invList_getByIndex(InvList invList, int index);
InvList invList_init(int maxInv);
void invList_free(InvList);
void invList_append(InvList* invList, Inv inv);
void invList_print(InvList invList);






#endif
