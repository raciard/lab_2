#include "list.h"
#include "Item.h"
#include <stdlib.h>
struct node{
	Link next;
	Item val;
};


Link newNode(Item item){
	Link l = malloc(sizeof(struct node));
	l->val = item;
	return l;
}


Link listInsert(Link l, Item item){
	Link node = newNode(item);

	Link prev;
	Link curr;

	if(l == NULL)
		return node;
	
	for(prev = NULL, curr = l;curr->next != NULL && item_Greater(item, curr->val); prev = curr, curr = curr->next);
	if(prev == NULL){
		node->next = l;
		return node;
	}
	node->next = curr->next;
	curr->next = node;

	return l;

} 


void listPrint(Link l){
	for(; l != NULL && l->val != NULL; l =  l->next){
		item_Print(l->val);
	}
}

Item listSearchElem(Link l, Key k){
	Link prev, curr;
	for(prev = NULL, curr = l; curr != NULL; prev = curr, curr = curr->next){
		if(item_KeyCompare(item_GetKey(curr->val), k) == 0){
			return curr->val;
		}
	}
	return NULL;
}


Item listExtractElem(Link* lp, Key k){
	Link l = *lp;
	Link prev, curr;
	if(l == NULL){
	
		return NULL;
	}
	for(prev = NULL, curr = l; curr != NULL; prev = curr, curr = curr->next){
	if(item_KeyCompare(item_GetKey(curr->val), k) == 0){
		if(prev == NULL){
			Link next = curr->next;
			*lp = next;
			Item val = curr->val;
			free(curr);
			return val;
		}
		prev->next = curr->next;
		Item val = curr->val;
		free(curr);
		return val;
	}
	}
	return NULL;
}

Link listExtractSeq(Link *l, char* dateS, char* dateF){
	Link prevStart, start, prevEnd, end;
	for(prevStart = NULL, start = *l;start->next != NULL && item_dateCompare(start->val, dateS) <= 0; prevStart = start, start = start->next);
	
	for(prevEnd = NULL, end = start ;end->next != NULL && item_dateCompare(end->val, dateF) > 0; prevEnd = end, end = end->next);

	if(prevStart == NULL){
		*l = end;
	}
	else{
		prevStart->next = end->next;
		end->next = NULL;
	}
	return start;



}
