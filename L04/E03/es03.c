#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "input/easy_test_set.txt"
typedef enum {Z, R, T, S} Pietra;

typedef struct {
	int z; int r; int t; int s;
} NumPietre;

int check(Pietra pre, Pietra curr){
	return pre == Z && (curr == Z || curr == R)
 || pre == S && (curr == S || curr == T)
|| pre == R&& (curr == S || curr == T)
 || pre == T&& (curr == Z || curr == R);
}

int collana_r(int* nPietre, int* sol, int cnt,  int* maxDim, int k){
	if(*maxDim == (k -1)){
		return 1;
	}
	int stop = 1;
	for(int i = 0; i <= S; i++){
		if(nPietre[i] > 0){
			Pietra curr = i;
			if(check(sol[cnt], curr)){
				stop = 0;
				sol[cnt+1] = i;
				nPietre[i]--;
				if(collana_r(nPietre, sol, cnt + 1, maxDim, k))
					return 1;
				nPietre[i]++;
			}
		}
		
	}
	if(stop){
		if(*maxDim < cnt){
			*maxDim = cnt;
		}

	}

	
	return 0;

}
int collana(int* nPietre){
	int k = nPietre[Z] + nPietre[R] + nPietre[T] + nPietre[S];
	int* sol = malloc((k) * sizeof(int));
	int maxDim = 0;
	for(int i = 0; i <= S; i++){
		if(nPietre[i] > 0){
			Pietra curr = i;
			sol[0] = i;
			nPietre[i]--;
			if(collana_r(nPietre, sol, 0, &maxDim, k))
				return maxDim + 1;
			nPietre[i]++;
		}
		
	}
	free(sol);
	return maxDim+1;
}


void leggiFile(FILE* fIn){
	int nTests;
	int nPietre[4];
	fscanf(fIn, "%d", &nTests);
	for(int i = 0; i < nTests; i++){
		//printf("Leggo test %d", i);
		fscanf(fIn, " %d %d %d %d ", &nPietre[Z], &nPietre[R], &nPietre[T], &nPietre[S]);
		//printf(" %d %d %d %d ", nPietre.z, nPietre.r, nPietre.t, nPietre.s);
		int n = collana(nPietre);
		printf("Test #%d: risultato %d\n", i+1 ,n);
	}
}


int main(){
	FILE* fIn = fopen(FILE_NAME, "r");
	leggiFile(fIn);
//	printf("%d", collana(nPietre));
}
