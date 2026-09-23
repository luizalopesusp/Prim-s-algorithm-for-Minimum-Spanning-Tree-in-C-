#ifndef GRAFO_MATRIZADJ_H
#define GRAFO_MATRIZADJ_H

#include <stdbool.h>

#define MAXNUMVERTICES 100
#define ARESTA_NULA -1  /* Indica ausência de aresta */

typedef int Peso;

typedef struct {
    Peso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int numVertices;
    int numArestas;
} Grafo;

/* Protótipos das funções básicas para você implementar e testar */
bool inicializaGrafo(Grafo* grafo, int nv);
bool insereAresta(Grafo* grafo, int v1, int v2, Peso peso);
void exibeGrafo(const Grafo* grafo);

#endif // GRAFO_MATRIZADJ_H