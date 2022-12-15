#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int s;
	int f;
} Att;

int isCompatible(Att a, Att* b, int* s, int n){
	for(int i = 0; i < n; i++){
		if (((a.s < b[s[i]].f) && (b[s[i]].s < a.f)))
			return 0;
	}
	return 1;
}
int find(int v[], int n, int val){
	for(int i = 0; i < n; i++){
		if(v[i] == val)
			return 1;
	}
	return 0;
}
typedef struct {
	int sol[5];
	int n;
	int d;
} Sol;

void attSel_r(Att* v, int n, int sol[], int nSol, int curr, Sol* sMax){


	int nComp = 0;
	for(int i = curr; i < n; i++){
		if (!find(sol,nSol, i) && isCompatible(v[i], v, sol, nSol)){
			sol[nSol] = i;
			attSel_r(v, n, sol, nSol + 1, i, sMax);
			nComp++;
		}
	}	
	if(nComp == 0){
		int d = 0;
		for(int j = 0; j < nSol; j++){
			d += v[sol[j]].f - v[sol[j]].s;
		}
		if(sMax->d <  d){
			for(int j = 0; j < nSol; j++){
				sMax->sol[j] = sol[j];
				sMax->d = d;
				sMax->n = nSol;
			}
		}	
	}
}

void attSel(int N, Att* v){
	Sol s;
	s.d = 0;

	int* sol = malloc(sizeof(int) * N);
	int max;
	attSel_r(v, N, sol, 0, 0, &s);

	printf("Il massimo è: ");
	for(int i = 0; i < s.n; i++){

		printf("(%d, %d)", v[s.sol[i]].s, v[s.sol[i]].f);
	}
	free(sol);
}
int readAtts(FILE* fin, Att** atts){
	int nAtts; 
	fscanf(fin, "%d", &nAtts);
	*atts = malloc(sizeof(Att) * nAtts);
	for(int i = 0; i< nAtts; i++){
		fscanf(fin, "%d %d", &(*atts)[i].s, &(*atts)[i].f);
	}
	return nAtts;
}


int main(){
	
	FILE* fin = fopen("att1.txt", "r");
	Att* atts;
	int nAtts;
	if(fin == NULL){
		printf("Errore lettura file!\n");
		return -1;
	}
	nAtts = readAtts(fin, &atts);


		

	attSel(nAtts, atts);




}
