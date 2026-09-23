#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "grafo.h"

//estruturas para nos e grafo
typedef struct no {
    int vizinho;
    float peso;
    struct no* prox;
}No;

struct grafo{
    int numV;
    int numA;
    No** listaAdj;//vetor onde cada posicao guarda o inicio de uma lista ligada
};

//função auxiliar que verifica a validade de vertices (não pode ser negativo nem maior que o numero total de vertices)
static bool verifica_validade_vertice(Grafo* g, int v){
    //se g é nulo, então retorna false
    if(g == NULL) return false;
    //se v é negativo ou é maior que o número de vértices do grafo(não existe), então retorna falso
    if(v < 0){
        printf("ERRO: Numero do vertice (%d) deve ser positivo.\n",v);
        return false;
    }
    if(v >= g->numV){
        printf("ERRO: Numero do vertice (%d) é maior que o numero total de vertices.\n",v);
        return false;
    }
    //c.c. retorna verdadeiro
    return true;
}

//funcao auxiliar para pegar o numero de vertices no grafo
int pegaNumVertices(Grafo* g){
    if (g == NULL) return 0;
    return g->numV;
}

//inicializa grafo
Grafo* inicializaGrafo(int numVertices){
    //verificando se o numero de vertice é negativo
    if(numVertices <= 0){
        printf("ERRO: %d  - Numero de vertices deve ser positivo", numVertices);
        return NULL;
    }
    //alocando memoria para o grafo
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    //caso a alocação não ocorra por algum motivo
    if(g == NULL) return NULL;

    g->numV = numVertices;
    g->numA = 0;

    //garantindo que todas as posições comecem com null
    g->listaAdj = (No**) calloc(numVertices, sizeof(No*));
    if(g->listaAdj == NULL){
        free(g);
        return NULL;
    }

    //retornando o grafo
    return g;
}

//liberando memoria do grafo
void liberaGrafo(Grafo* g){
    if(g != NULL){
        //liberando a lista de vizinhos
        for(int i = 0; i < g->numV; i++){
            No* atual = g->listaAdj[i];
            while(atual != NULL){
                No* apagar = atual;
                atual = atual->prox;
                free(apagar);
            }
        }
        //liberando vetor e grafo
        free(g->listaAdj);
        free(g);
    }
}

//inserindo arestas
bool insereAresta(Grafo* g, int v1, int v2, float peso){
    //verificando o grafo
    if(g == NULL) return false;

    //flags auxiliares
    bool ha_erro = false;
    bool vertices_validos = true;

    //verificando os vertices
   if(!verifica_validade_vertice(g,v1)){
        printf("ERRO: VERTICE INVALIDO (%d)\n",v1);
        ha_erro = true;
        vertices_validos = false;
    }
    if(!verifica_validade_vertice(g,v2)){
        printf("ERRO: VERTICE INVALIDO (%d)\n",v2);
         ha_erro = true;
        vertices_validos = false;
    }
    //verificando auto laço
    if(v1 == v2){
        printf("ERRO: AUTO-LACO (%d,%d)\n",v1,v2);
        ha_erro = true;
    }
    
    //so entra aqui se houver vertices
    if(vertices_validos){
        //inicia no primeiro vizinho de v1
        No* atual = g->listaAdj[v1];
        //verificando aresta paralela
         while(atual != NULL){
            if(atual->vizinho == v2){
                //encontrando qual o maior e menor numero para imprimir em ordem crescente
                int menor = (v1 < v2) ? v1:v2;
                int maior = (v1 > v2) ? v1:v2;
                printf("ERRO: ARESTA PARALELA (%d,%d)\n",menor,maior);
                ha_erro = true;
                break;
            }
            atual = atual->prox;
        }
    }

    //verificando peso
    if(peso <= 0){
        printf("ERRO: PESO INVALIDO (%.1f)\n",peso);
        ha_erro = true;
    }

    //se houver erro, nao insere
    if(ha_erro){
        return false;
    }

    //insere v2 na lista de v1
    No* novoNo1 = (No*) malloc(sizeof(No));
    novoNo1->vizinho = v2;
    novoNo1->peso = peso;
    novoNo1->prox = g->listaAdj[v1];
    g->listaAdj[v1] = novoNo1;

    //insere v1 na v2
    No* novoNo2 = (No*) malloc(sizeof(No));
    novoNo2->vizinho = v1;
    novoNo2->peso = peso;
    novoNo2->prox = g->listaAdj[v2];
    g->listaAdj[v2] = novoNo2;

    //acrescenta aresta
    g->numA++;

    return true;
}

//pegando os vizinhos dos vertices
int* pegaVizinhos(Grafo* g, int vertice, int* numVizinhos){
    //verificando vertice
    if(!verifica_validade_vertice(g, vertice)){
        *numVizinhos = 0;
        return NULL;
    }
    //contagem dos vizinhos
    int cont = 0;
    No* atual = g->listaAdj[vertice];
    while(atual != NULL){
        cont++;
        atual = atual->prox;
    }
    //guarda a contagem
    *numVizinhos = cont;

    //se não houver vizinhos, entao retorna nulo
    if(cont == 0){
        return NULL;
    }

    //alocando memoria pro vetor
    int* vizinhos = (int*) malloc(cont*sizeof(int));

    //preenchendo o vetor com os vizinhos do vertice
    atual = g->listaAdj[vertice];
    int indice = 0;
    while(atual != NULL){
        vizinhos[indice] = atual->vizinho;
        indice++;
        atual = atual->prox;
    }

    //retornando vetor
    return vizinhos;
}

//pegando peso da aresta
float pegaPesoAresta(Grafo* g, int v1, int v2) {
    if (!verifica_validade_vertice(g, v1) || !verifica_validade_vertice(g, v2)) {
        return -1.0;
    }
    No* atual = g->listaAdj[v1];
    while (atual != NULL) {
        if (atual->vizinho == v2) {
            return atual->peso;
        }
        atual = atual->prox;
    }
    return 0.0;
}
