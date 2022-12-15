#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int s;
	int f;
} Att;

int isCompatible(Att a, Att b){
	return !((a.s < b.f) && (b.s < a.f));
}

int longest(Att* v, int* l, int* prec, int index){
	int max = 0;
	int maxPrec = index;
	for(int i = 0; i < index; i++){
		if(isCompatible(v[i], v[index])){
			int r = l[i];
			if(r > max){
				max = r;
				maxPrec = i;
			}
		}
	}
	prec[index] = maxPrec;
	return v[index].f - v[index].s + max;
}

int attSel_nonR(int N, Att* v){
	int* l = calloc(N, sizeof(int));
	int* prec = calloc(N, sizeof(int));
	l[0] = v[0].f - v[0].s;
	prec[0] = 0;
	for(int i = 1; i < N; i++){
		int maxPrec = i;
		for(int j = 0; j < i; j++){
			if(isCompatible(v[i], v[j])){
				int r = l[j];
				if(r > l[maxPrec]){
					maxPrec = j;
				}
			}
		}
		prec[i] = maxPrec;
		l[i] = v[i].f - v[i].s + l[maxPrec];
 
	}
	int max= 0;
	int ending = -1;
 	for(int i = 0; i < N; i++){
		if(max < l[i]){
			max = l[i];
			ending = i;
		
		}
	}

	while(prec[ending] != ending){
		printf("(%d, %d)\n",v[ending].s, v[ending].f);
		ending = prec[ending];
	}

	printf("(%d, %d)\n",v[ending].s, v[ending].f);
	

	free(l);

	return max;
}
int compareAtt(const void* att1, const void*  att2){
	return (((Att*)att2)->s - ((Att*)att1)->s);
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


		

	qsort(atts, nAtts, sizeof(Att), compareAtt);
	printf("La lunghezza massima delle attività lette da file è: %d ", attSel_nonR(nAtts, atts) );


}
