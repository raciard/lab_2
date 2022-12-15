#include <stdio.h>
#include "Pg.h"
#include "menu.h"
#include "InvList.h"
#include "pglist.h"


int main(){
	Choice choices[9] = {{"Chiudi tutto.", "fine"},{"Carica personaggi e items.", "load"} ,{"Stampa personaggi.", "stampa"} ,{"Aggiungi/Rimuovi oggetto a personaggio.", "itemtoggle"}, {"Visualizza equipaggiamento e calcola statistiche personaggio.", "stats"},  
		{"Elimina un personaggio.", "delpg"}, {"Aggiungi personaggio.", "addpg"}, {"Visualizza items disponibili", "itemshow"},{"mostra questo menu", "h"},};
	PgList pgList = pgListInit();
	InvList invList;
	print_menu(choices, 9);
	while(1){
	int c = scan_choice(choices, 9);
	switch (c){
		case 0:
			invList_free(invList);
			pgListFreeALl(pgList);
			return 0;
		case 1:{
				   char fileName[100];
				   FILE* fPers, *fInv;
				   Pg pg;
				   printf("Inserisci il nome del file dei personaggi: ");
				   scanf("%s", fileName);
				   if((fPers = fopen(fileName, "r") ) == NULL){
					   printf("Errore nella lettura del file!\n");
					   continue;
				   }
				   while((pg = pg_read(fPers)) != NULL){
					   pgListInsTail(pgList, pg);
				   }
				   printf("Inserisci il nome del file degli equipaggiamenti: ");
				   scanf("%s", fileName);
				   if((fInv = fopen(fileName, "r") ) == NULL){
					   printf("Errore nella lettura del file!\n");
					   continue;
				   }
				   int maxInv;
				   fscanf(fInv,"%d", &maxInv);
				   invList = invList_init(maxInv);
				   for(int i = 0; i < maxInv; i++){
					   invList_append(&invList, inv_read(fInv));
				   }


				   printf("\n");
				   break;
			   }
		case 2:{
				   pgListPrint(pgList);
				   break;
			   }
		case 3: {
					char persCode[50], invName[50];
					printf("\nInserisci codice personaggio: ");
					scanf("%s", persCode);
					Pg pg = pgListSearchElem(pgList, persCode);	
					if(pg == NULL){
						printf("Personaggio non trovato\n");
						continue;
					}

					printf("Inserisci nome oggetto da aggiungere/rimuovere dall'inventario: ");
					scanf("%s", invName);
					int index =  invList_find(invList, invName);
					if(index == -1){
						printf("Oggetto non trovato\n");
						continue;
					}
					if(pg_hasEquip(pg, index)){
						pg_removeEquip(pg, index);
						printf("Oggetto rimosso dal personaggio\n");
					} else {
						pg_addEquip(pg, index);
						printf("Oggetto aggiunto al personaggio!\n");
					}
					break;
				}
		case 4:{
				    char persCode[50];
					printf("Inserisci codice personaggio: ");
					scanf("%s", persCode);
					Pg pg = pgListSearchElem(pgList, persCode);	
					if(pg == NULL){
						printf("Personaggio non trovato\n");
						break;
					}
					pg_printAndGetStats(pg, invList);
					

				    break;



			   }
		case 5:{
				    char persCode[50];
					printf("Inserisci codice personaggio: ");
					scanf("%s", persCode);
					Pg pg = pgListExtractElem(pgList, persCode);	
					if(pg == NULL){
						printf("Personaggio non trovato\n");
						continue;
					}
					printf("Personaggio eliminato: \n");
					pg_print(pg);
					pg_free(pg);



				   break;
			   }
		case 6:{
				   	Pg pg;
				   	printf("Inserisci dati personaggio: <codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>: \n");
					pg = pg_read(stdin);
					if(pg == NULL){
						printf("Errore lettura personaggio");
					}
					else{
						pgListInsTail(pgList, pg);
						printf("Personaggio inserito correttamente");
					}

				   

					break;
			   }
		case 7:{
				   invList_print(invList);
				   break;
			   }
		case 8:{
				   print_menu(choices, 9);
				   break;
			   }
		default: {
					 printf("Non ho capito!");
				 }

	
		
		}
		printf("\n\n");
	}
}
