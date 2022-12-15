#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
	char color1;
	int val1;
	char color2;
	int val2;
} Tile;


typedef struct {
	Tile** tiles;
	int NR, NC;
	int nVoid;
	Tile** voids;
} Board;

typedef struct {
	Tile *p;
	int nPieces;
} Pieces;

int getPartialScore(Tile** tiles, int NR, int NC, int orientation){
	int returnSum = 0;
	if(orientation == 1){
		int tmp = NC;
		NC = NR;
		NR = tmp;
	}
	for(int r = 0; r < NR; r++){
		char prevCol = orientation == 0 ? tiles[r][0].color1 : tiles[0][r].color2;
		int sum = orientation == 0 ? tiles[r][0].val1 : tiles[0][r].val2;
		for(int c = 1; c < NC; c++){
			if(orientation && tiles[c][r].color2 == prevCol ){
				sum += tiles[c][r].val2;
			}
			else if(orientation == 0 && tiles[r][c].color1 == prevCol){
				sum += tiles[r][c].val1;
			}
			else{
				sum = -1;
				break;
				
			}

		}
		if(sum == -1){
			continue;
		}
		returnSum += sum;
	}
	return returnSum;
	
}

int getBoardScore(Board b){
	return getPartialScore(b.tiles, b.NR, b.NC, 0) + getPartialScore(b.tiles, b.NR , b.NC, 1);
}

Pieces readPieces(FILE* fIn){
	int nPieces;
	Tile* pieces;
	fscanf(fIn, "%d", &nPieces);
	pieces = malloc(sizeof(Tile) * nPieces);
	for(int i = 0; i < nPieces; i++){
		fscanf(fIn, " %c %d %c %d", &pieces[i].color1, &pieces[i].val1, &pieces[i].color2, &pieces[i].val2);
	}
	Pieces p = {pieces, nPieces};
	return p;

}

Tile swapTile(Tile t){
	int tmp = t.val1;
	t.val1 = t.val2;
	t.val2 = tmp;
	char tmp2 = t.color1;
	t.color1 = t.color2;
	t.color2 = tmp2;
	return t;

}

void solToBoard(Board b, int* sol, int nSol, Pieces p){
		for(int i=0; i < nSol; i++){
			*b.voids[i] = sol[i] >= 0 ? p.p[sol[i]] : swapTile(p.p[-sol[i] - 1]);
		}
}

//Risolvo utilizzando disposizioni semplici
int fillBoard_r(Board b,  int maxm, Pieces p, int* sol, int nSol, int* mark, int* maxSol){
	if(b.nVoid == nSol){
		solToBoard(b, sol, nSol, p);
		int score = getBoardScore(b);
		if(score > maxm){
			maxm = score;
			memcpy(maxSol, sol, sizeof(int) * nSol);
		}
		return maxm;
	}
	
	
	for(int i = 0; i < p.nPieces; i++){
		if(mark[i] == 0 ){
		mark[i] = 1;
		sol[nSol] = i;
		int m1 = fillBoard_r(b, maxm, p, sol, nSol +1 , mark, maxSol);

		sol[nSol] = -i-1;
		int m2 = fillBoard_r(b, maxm, p, sol, nSol +1 , mark, maxSol);
		mark[i] = 0;
		if(m1 > maxm)
			maxm = m1;
		if(m2 > maxm)
			maxm = m2;

		}
	}

	return maxm;

}

int fillBoard(Board b, Pieces p, int* mark){
	int* sol = malloc(sizeof(int) * b.nVoid);
	int* maxSol = malloc(sizeof(int) * b.nVoid);

	int m = fillBoard_r(b, 0, p, sol, 0, mark, maxSol);
	solToBoard(b, maxSol, b.nVoid, p);

	free(sol);
	free(maxSol);
	return m;

}



Board readBoard(FILE* fIn, Pieces p, int* mark){
	Board b;
	fscanf(fIn, " %d %d", &b.NR, &b.NC);
	b.tiles = malloc(sizeof(Tile*) * b.NR);
	b.nVoid = 0;
	b.voids = malloc(sizeof(Tile*) * b.NR * b.NC);
	for(int i = 0; i< b.NR; i++){
		b.tiles[i] = malloc(sizeof(Tile) * b.NC);
		for(int j = 0; j < b.NC; j++){
			int index, rot;
			fscanf(fIn, " %d/%d", &index, &rot);
			if(index != -1){
				mark[index] = 1;
				if(rot == 0){
					b.tiles[i][j] = p.p[index];
				}
				else{
					b.tiles[i][j] = swapTile(p.p[index]) ;

				}
			}
			else {
				b.tiles[i][j].color1 =  -1;
				b.voids[b.nVoid++] = &b.tiles[i][j]; 
			}
		}
	}
	return b;
}

void freeBoard(Board b){
	for(int r = 0; r< b.NR; r++){
		free(b.tiles[r]);
	}
	free(b.tiles);
	free(b.voids);
}

void freeTiles(Pieces p){
	free(p.p);
}

void printBoard(Board b){
	printf("Verticali    |    Orizzontali\n");
	for(int i = 0; i < b.NR; i++){
		for(int j = 0; j < b.NC; j++){
			printf("%c %d   |   %c %d           ", b.tiles[i][j].color1, b.tiles[i][j].val1, b.tiles[i][j].color2, b.tiles[i][j].val2);
		}
		printf("\n");
	}
}

int main(){

	FILE* fin = fopen("tiles.txt", "r");
	Pieces p = readPieces(fin);
	fclose(fin);
	int* mark = calloc(p.nPieces, sizeof(int));
	fin = fopen("board.txt", "r");
	Board b = readBoard(fin, p, mark);
	int* sol = malloc(sizeof(int) * b.nVoid);
	int* maxSol = malloc(sizeof(int) * b.nVoid);
	
	printf("Il punteggio massimo è: %d \n", fillBoard(b, p, mark));

	printf("Soluzione: \n");

	printBoard(b);

	freeBoard(b);
	freeTiles(p);
	
	fclose(fin);
}

