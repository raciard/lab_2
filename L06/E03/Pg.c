#include "Pg.h"
#include <stdio.h>
#define maxS 50
#define MAXEQ 8
typedef struct{
	int nEq;
	int vettEq[MAXEQ];
} Equip;
struct i {
	char codice[maxS];
	char nome[maxS];
	char classe[maxS];
	Equip equip;
	Stats stats;
};


void pg_free(Pg item){
	free(item);
}
Pg pg_init(){
	Pg pg = malloc(sizeof(struct i));
	return pg;
}

Pg pg_read(FILE* fIn){
	Pg item = malloc(sizeof(struct i));

	if(fscanf(fIn, "%s %s %s %d %d %d %d %d %d ", item->codice, item-> nome, item->classe, &item->stats.hp,
				&item->stats.mp, &item->stats.atk, &item->stats.def, &item->stats.mag, &item->stats.spr) != 9){
		free(item);
		return NULL;
	}

	return item;

}

void pg_addEquip(Pg item, int invIndex){
	if(item->equip.nEq < MAXEQ){
		item->equip.vettEq[item->equip.nEq] = invIndex;
		item->equip.nEq++;
	}
}
void pg_removeEquip(Pg item, int invIndex){
	for(int i = 0; i < item->equip.nEq; i++){
		if(item->equip.vettEq[i] == invIndex){
			for(int j = i; j < (item->equip.nEq - 1); j++ ){
				item->equip.vettEq[j] = item->equip.vettEq[j+1];
			}
			item->equip.nEq--;
		}
	}
}

int  pg_hasEquip(Pg item, int invIndex){
	for(int i = 0; i < item->equip.nEq; i++){
		if(item->equip.vettEq[i] == invIndex)
			return 1;
	}
	return 0;
}

Stats sumStats(Stats a, Stats b){
	a.atk += b.atk;
	a.def += b.def;
	a.hp += b.hp;
	a.mag += b.mag;
	a.mp += b.mp;
	a.spr += b.spr;
	if(a.atk == 0)
		a.atk = 0;
	if(a.def == 0)
		a.def = 0;
	if(a.hp == 0)
		a.hp = 0;
	if(a.mag == 0)
		a.mag = 0;
	if(a.mp == 0)
		a.mp = 0;
	if(a.spr == 0)
		a.spr = 0;
	return a;

}

void printStats(Stats s){
	printf("%d %d %d %d %d %d\n", s.hp, s.mp, s.atk, s.def, s.mag, s.spr);

}
Stats pg_getStats(Pg item, InvList invList){
	Stats s = item->stats;
	for(int i = 0; i < item->equip.nEq; i++){
		s = sumStats(s, invList_getByIndex(invList, item->equip.vettEq[i]).stats);	

	}
	return s;
	

}

void pg_print(Pg item){
	printf("%s %s %s\n", item-> codice, item->nome, item->classe);
	printf("\t Statistiche base: "); 
	printStats(item->stats);
	printf("\n");
}
void pg_printAndGetStats(Pg item, InvList invList){
	pg_print(item);
	printf("\tOggetti equipaggiati: \n");
	for(int i = 0; i < item->equip.nEq; i++){
		printf("\t  - %s\n", invList_getByIndex(invList, item->equip.vettEq[i]).nome);
	}
	printf("\t Statistiche con modificatori: ");
	printStats(pg_getStats(item, invList));
	printf("\n");
}
int pg_compare(Pg item1, Key k){
	return strcmp(item1->codice, k);
}
