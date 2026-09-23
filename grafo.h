//arquivo .h para guardar os cabeçalhos das funções utilizadas

#ifndef GRAFO_H
#define GRAFO_H
#include <stdbool.h>
#define MAXNUMVERTICES 100

//passando estrutura do grafo
typedef struct grafo Grafo;

//funções
//aloca a memoria necessaria para o grafo, tanto para matriz quanto para lista
Grafo* inicializaGrafo(int numVertices);

//libera a memoria alocada
void liberaGrafo(Grafo* g);

//insere aresta entre dois vertices
bool insereAresta(Grafo* g, int v1, int v2, float peso);

//retorna vetor contendo os vizinhos
int* pegaVizinhos(Grafo* g, int vertice, int* numVizinhos);

//pega o numero de vertices
int pegaNumVertices(Grafo* g);

//pega peso da aresta
float pegaPesoAresta(Grafo* g, int v1, int v2);

#endif