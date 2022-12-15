#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>


typedef struct i* Item;
typedef char* Key;


Key item_GetKey(Item item);
int item_KeyCompare(Key first_operand, Key second_operand);
int item_Greater(Item first_operand, Item second_operand);
int item_Less(Item first_operand, Item second_operand);
Item item_Read(FILE* fIn);
void item_Print(Item item);
void item_Free(Item item);
int item_dateCompare(Item, char*);
Item item_getNULL();










#endif
