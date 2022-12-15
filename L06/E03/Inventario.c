#include "Inventario.h"
#include <stdio.h>



Inv inv_read(FILE* fIn){
	Inv inv;
	fscanf(fIn, "%s %s %d %d %d %d %d %d", inv.nome, inv.tipo, &inv.stats.hp, &inv.stats.mp, &inv.stats.atk, &inv.stats.def, &inv.stats.mag, &inv.stats.spr);
	return inv;
}
void inv_print(FILE* fOut, Inv inv){
	fprintf(fOut, "%s %s", inv.nome, inv.tipo);
}


