#include "Item.h"
#include "list.h"
#include <stdio.h>
#include "menu.h"

#define FILENAME "anag1.txt"





int main(){
	Link list = NULL;
	Choice choices[7] = {{"Aggiungi elemento da tastiera.", "aggiungi"}, 
		{"Leggi elementi da File.", "leggi"},
		{"Ricerca elemento per codice. ", "cerca"},
		{"Cancella un elemento.", "cancella"},
		{"Stampa su schermo.", "schermo"},
		{"Estrai intervallo date nascita.", "estint"},
		{"Chiudi programma.", "fine"}
	};
	while(1){
	int ca= menu_print_and_scan(choices, 7);
	switch(ca){
		case 0: {
			printf("Inserisci elemento: <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap> \n");
			Item item = item_Read(stdin);		
			list = listInsert(list, item);
			break;
		}
		case 1: {
			Item item;
			char nomeFile[50];
			printf("Inserisci nome del file da leggere: ");
			scanf("%s", nomeFile);
			FILE* fIn = fopen(nomeFile, "r");
			if(fIn == NULL){
				printf("Errore nella lettura del file\n");
				break;
			}
			while((item = item_Read(fIn)) != NULL){
				list = listInsert(list, item);	
			}
			

			break;
		}
		case 2: {
					char chiave[50];
					printf("Inserisci una chiave da cercare: ");
					scanf("%s", chiave);
					Item i = listSearchElem(list, chiave);
					if(i != NULL)
						item_Print(i);
					else printf("Elemento non trovato\n");


					break;

				}
		case 3: {
					char chiave[50];
					printf("Inserisci la chiave dell'elemento da estrarre: ");
					scanf("%s", chiave);
					Item i = listExtractElem(&list, chiave);
					if(i != NULL)
						item_Print(i);
					else printf("Elemento non trovato\n");


					
					
					break;

				}

		case 4: {
					printf("\n\n\n");
					listPrint(list);
					printf("\n\n\n");
					break;
				}
		case 5:{
				   char data1[50];
				   char data2[50];
				   printf("Inserisci la prima data dell'intervallo (AAAA/MM/GG): ");
				   scanf("%s", data1);
				   printf("\nInserisci la seconda data dell'intervallo: ");
				   scanf("%s", data2);
				   Link interv = listExtractSeq(&list, data1, data2);
				   printf("Elementi eliminati: \n");
				   listPrint(interv);
				   printf("\n");
				   break;
				   
			   }
		case 6:{
				   return 0;

				   break;
			   }

	}
	}

}
