#ifndef PG_H
#define PG_H

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include "InvList.h"



typedef struct i* Pg;
typedef char* Key;


Pg pg_read(FILE* fIn);
void pg_print(Pg item);
void pg_free(Pg item);
Pg pg_getNULL();
int pg_compare(Pg intem, Key k);
void pg_addEquip(Pg item, int invIndex);
void pg_printAndGetStats(Pg item, InvList invList);

int  pg_hasEquip(Pg item, int invIndex);
void pg_removeEquip(Pg item, int invIndex);









#endif
