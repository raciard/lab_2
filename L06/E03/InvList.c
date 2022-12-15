#include "InvList.h"



InvList invList_init(int maxInv){
	InvList invList;
	invList.vettInv = malloc(sizeof(Inv) * maxInv);
	invList.maxInv = maxInv;
	invList.nInv = 0;
	return invList;
}

void invList_free(InvList invList){
	if(invList.vettInv != NULL)
		free(invList.vettInv);
	invList.maxInv=0;
	invList.nInv=0;
}

void invList_append(InvList* invList, Inv inv){
	if(invList->maxInv > invList->nInv){
		invList->vettInv[invList->nInv] = inv;
		invList->nInv++;
	}
}

int invList_find(InvList invList, char* nome){
	for(int i = 0; i < invList.nInv; i++ ){
		if(strcmp(invList.vettInv[i].nome, nome) == 0){
			return i;
		}
	}
	return -1;
}
void invList_print(InvList invList){
	for(int i = 0; i < invList.nInv; i++){
		inv_print(stdout, invList.vettInv[i]);
		printf("\n");
	}

}
Inv invList_getByIndex(InvList invList, int index){
	return invList.vettInv[index];
}

