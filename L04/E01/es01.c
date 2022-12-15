#include <stdio.h>
#include <stdlib.h>

#define FILENAME "grafo.txt"

typedef struct {
	int a;
	int b;
} Link;


typedef struct {
	Link* links;
	int nLinks;
	int* vertexes;
	int nVertexes;
} Graph;

Graph readGraph(FILE* f){
	Graph graph;
	int maxVertexes;
	fscanf(f, " %d %d", &maxVertexes, &graph.nLinks);
	graph.links = malloc(sizeof(Link) * graph.nLinks);
	graph.vertexes = malloc(sizeof(int) * maxVertexes);
	graph.nVertexes = 0;
	for(int i = 0; i < graph.nLinks; i++){
		fscanf(f, " %d %d", &graph.links[i].a, &graph.links[i].b);
		int foundA = 0, foundB = 0;
		for(int j = 0; j < graph.nVertexes; j++){
			if(graph.vertexes[j] == graph.links[i].a){
				foundA = 1;
			}
			if(graph.vertexes[j] == graph.links[i].b){
				foundB = 1;
			}

		}
		if(!foundA)
			graph.vertexes[graph.nVertexes++] = graph.links[i].a; 
		if(!foundB)
			graph.vertexes[graph.nVertexes++] = graph.links[i].b; 
	}
	return graph; 
}



int areVertexesInLink(Link link, int* vertexes, int nVertexes){
//	printf("Link (%d, %d): \n", link.a, link.b);
	for(int i =0; i < nVertexes; i++){
	//	printf(" controllo vertice %d\n", vertexes[i]);
		if(vertexes[i] == link.a || vertexes[i] == link.b)
			return 1;
	}
	return 0;

}

int isVertexCover(Link* links, int* vertexes, int nLinks, int nVertexs){
	for(int i = 0; i < nLinks; i++){
		if(!areVertexesInLink(links[i], vertexes, nVertexs))
			return 0;
	}
	return 1;


}
int powerset(Graph graph,int pos,int *sol, int cnt) {
	Link* links = graph.links;
	int n = graph.nVertexes;
	int nLinks = graph.nLinks;
	int j;
	if (pos >= n) {
	  int* vertexes = malloc(sizeof(int) * n);
	  int i = 0;
	  for (j=0; j<n; j++)
		if (sol[j]!=0){
			vertexes[i] =graph.vertexes[j] ;
			i++;
		}
	  if(isVertexCover(links, vertexes, nLinks, i)){
		  printf("( ");
		  for(int k = 0; k < i; k++){
			  printf("%d ", vertexes[k]);
		  }
		  printf(")");
	  } 
	  return cnt+1; 
	}
	sol[pos] = 0;
	cnt = powerset(graph, pos+1, sol, cnt);
	sol[pos] = 1;
	cnt = powerset(graph, pos+1,sol, cnt);
	return cnt;
}




void vertexCovers(Graph graph){
	int* sol = calloc( graph.nLinks, sizeof(int));
	printf("I vertex cover del grafo letto sono: \n");
	powerset(graph, 0,sol, 0);

}


void freeGraph(Graph graph){
	free(graph.links);
	free(graph.vertexes);
	graph.nLinks = 0;
	graph.nVertexes = 0;
}



int main(){
	FILE* fin = fopen(FILENAME, "r");
	if(fin == NULL){
		printf("Errore lettura file\n");
		return -1;
	}
	Graph graph = readGraph(fin);
	vertexCovers(graph);
	freeGraph(graph);

}
