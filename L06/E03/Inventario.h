#ifndef INVENTARIO_H
#define INVENTARIO_H
#define MAXS 50

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int hp,
		mp,
		atk,
		def,
		mag,
		spr;
} Stats;

// QUASI ADT
typedef struct {
	char nome[MAXS], tipo[MAXS];
	Stats stats;
} Inv;

Inv inv_read(FILE* fIn);
void inv_print(FILE* fOut, Inv inv);




#endif

