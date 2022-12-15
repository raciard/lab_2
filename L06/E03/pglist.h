#ifndef PG_LIST_H
#define PG_LIST_H

typedef struct list* PgList;

#include "Pg.h"


PgList pgListInsTail(PgList l, Pg i);

Pg pgListExtractElem(PgList lp, Key k);
Pg pgListSearchElem(PgList l, Key k);
PgList pgListInit();
void pgListPrint(PgList list);
void pgListFreeALl(PgList);


void ListPrint(PgList list);

#endif
