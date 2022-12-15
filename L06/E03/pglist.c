#include "pglist.h"
#include "Pg.h"
#include <stdlib.h>
typedef struct node* Link; 
struct node{
	Link next;
	Pg val;
};

struct list{
	Link head;
	Link tail;
	int nElem;
};


Link newNode(Pg item){
	Link l = malloc(sizeof(struct node));
	l->val = item;
	return l;
}
PgList pgListInit(){
	PgList pgList = malloc(sizeof(struct list));
	pgList->nElem = 0;
	pgList->head = NULL;
	pgList->tail = NULL;
	return pgList;
}
PgList pgListInsTail(PgList l, Pg item){
	if(l->head == NULL){
		l->head = newNode(item);
		l->tail = l->head;
	}
	else {
		l->tail->next = newNode(item);
		l->tail = l->tail->next;
	} 
	return l;

} 


void pgListPrint(PgList list){
	Link link = list->head;	
	for(; link != NULL && link->val != NULL; link =  link->next){
		pg_print(link->val);
	}
}

Pg pgListSearchElem(PgList list, Key k){
	Link l = list->head;
	Link curr;
	for(curr = l; curr != NULL; curr = curr->next){
		if(pg_compare(curr->val, k) == 0){
			return curr->val;
		}
	}
	return NULL;
}


Pg pgListExtractElem(PgList list, Key k){
	Link l = list->head;
	Link prev, curr;
	if(l == NULL){
	
		return NULL;
	}
	for(prev = NULL, curr = l; curr != NULL; prev = curr, curr = curr->next){
		if(pg_compare(curr->val, k) == 0){
			if(prev == NULL){
				Link next = curr->next;
				list->head = next;
				Pg val = curr->val;
				free(curr);
				return val;
			}
			prev->next = curr->next;
			Pg val = curr->val;
			free(curr);
			return val;
		}
	}
	return NULL;
}


void pgListFreeALl(PgList pgList){
	Link curr, next;
	for(curr = pgList->head, next = pgList->head->next; curr != NULL; next = curr->next , curr = next)
		pg_free(curr->val);
	free(pgList);

}
