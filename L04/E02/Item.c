#include "Item.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define maxS 50
struct i {
	char code[maxS];
	char nome[maxS];
	char cognome[maxS];
	char birthDate[maxS];
	char road[maxS];
	char city[maxS];
	int cap;
};


Key item_GetKey(Item item){
	return item->code;
}


int item_KeyCompare(Key first_operand, Key second_operand){
	return strcmp(first_operand, second_operand);
}


int item_Greater(Item first_operand, Item second_operand){
	return strcmp(first_operand->birthDate, second_operand->birthDate) > 0; 
}
int item_dateCompare(Item i, char* date){
	return strcmp(i->birthDate, date);
}

int item_Less(Item first_operand, Item second_operand){
	return strcmp(first_operand->birthDate, second_operand->birthDate) < 0; 
}




void formatDate(char* s){
	char r[50],temp[50];
    int i,j,k,z,n;
    j = 0;
    for(n=strlen(s)-1; n>=0; n=i)
    {
        i=n;
        k=0;
        while(s[i]!='/' && s[i]!='-' && i >= 0)
        {
            temp[k++]=s[i];
            i--;
        }
        i--;
        temp[k] = '\0';
        for(z=strlen(temp)-1; z>=0; z--,j++)
        {
            r[j]=temp[z];
        }
        if(i >= 1) 
        {
            r[j++] = s[i + 1]; 
        }
        temp[0]='\0'; 
    }
    r[j] = '\0';
	strcpy(s, r);
	
}

void item_Free(Item item){
	free(item);
}


Item item_Read(FILE* fIn){
	Item item = malloc(sizeof(struct i));

	if(fscanf(fIn, "%s %s %s %s %s %s %d", item->code, item->nome, item->cognome, item->birthDate, item->road, item->city, &item->cap ) != 7){
		free(item);
		return NULL;
	}
	formatDate(item->birthDate);

	return item;

}


void item_Print(Item item){
	printf("%s %s %s\n", item-> nome, item->cognome, item->birthDate);
}
