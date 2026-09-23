#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//estrutura do grafo
struct grafo
{
    int numVertices;
    int numArestas;
    float** matriz;
};

//função auxiliar que verifica a validade de vertices (não pode ser negativo nem maior que o numero total de vertices)
static bool verifica_validade_vertice( Grafo* g, int v){
    //se g é nulo, então retorna false
    if(g == NULL) return false;
    //se v é negativo ou é maior que o número de vértices do grafo(não existe), então retorna falso
    if(v < 0){
        printf("ERRO: Numero do vertice (%d) deve ser positivo.\n",v);
        return false;
    }
    if(v >= g->numVertices){
        printf("ERRO: Numero do vertice (%d) é maior que o numero total de vertices.\n",v);
        return false;
    }
    //c.c. retorna verdadeiro
    return true;
}

//funcao auxiliar para pegar o numero de vertices no grafo
int pegaNumVertices(Grafo* g){
    if (g == NULL) return 0;
    return g->numVertices;
}

//inicializando grafo
Grafo* inicializaGrafo(int numVertices){
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));//alocando memoria para o grafo
    //tratamento em caso de falha de segmentação (alocação de memória deu erro)
    if(g != NULL){
        g->numVertices = numVertices;
        g->numArestas = 0;

        //alocando memoria para vetor de linhas
        g->matriz = (float**) malloc(numVertices * sizeof(float*));

        for(int i = 0; i < numVertices; i++){
            //garantindo que a matriz inicie sempre vazia
            g->matriz[i] = (float*) calloc(numVertices, sizeof(float));
        }
    }
    //retornando p grafo
    return g;
}

//liberando memória alocada pro grafo
void liberaGrafo(Grafo* g){
    if(g != NULL){
        //liberando as colunas
        for(int i = 0; i < g-> numVertices; i++){
            free(g->matriz[i]);
        }
        //liberando as linhas
        free(g->matriz);
        //liberando a estrutura principal
        free(g);
    }
}

//inserindo arestas no grafo
bool insereAresta(Grafo* g, int v1, int v2, float peso){
    //verificando se existe grafo
    if(g == NULL) return false;
    
    //flags auxiliares
    bool ha_erro = false;
    bool vertices_validos = true;

    //verificando a validade dos dois vertices
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
        //verificando aresta paralela
         if(g->matriz[v1][v2] != 0){
            //encontrando qual o maior e menor numero para imprimir em ordem crescente
            int menor = (v1 < v2) ? v1:v2;
            int maior = (v1 > v2) ? v1:v2;
            printf("ERRO: ARESTA PARALELA (%d,%d)\n",menor,maior);
            ha_erro = true;
        }
    }
   
    //verificando se peso é negativo, se for, retorna false
    if(peso <= 0){
        printf("ERRO: PESO INVALIDO (%.1f)\n",peso);
        ha_erro = true;
    }

    //cancela a inserçaõ se houver qualquer erro
    if(ha_erro){
        return false;
    }

    //atribuindo os pesos caso não haja erro nenhum
    g->matriz[v1][v2] = peso;
    g->matriz[v2][v1] = peso;
    g->numArestas++;

    return true;
}

//capturando vizinhos
int* pegaVizinhos (Grafo* g, int vertice, int* numVizinhos){
    //validando vertices, se for invalido, existem 0 vizinhos
    if(!verifica_validade_vertice (g,vertice)){
        *numVizinhos = 0;
        return NULL;
    }
    //contando os vizinhos na linha da matriz
    int cont = 0;
    for (int i = 0; i < g->numVertices; i++){
        if(g->matriz[vertice][i] != 0){
            cont++;
        }
    }
    *numVizinhos = cont;

    //se o vertice não tiver vizinhos retorna null
    if(cont == 0){
        return NULL;
    }

    //alocando memoria e guardando os vizinhos
    int* vizinhos = (int*) malloc(cont * sizeof(int));
    int indice = 0;
    for(int i = 0; i < g->numVertices; i++){
        if (g->matriz[vertice][i] != 0){
            vizinhos[indice] = i;
            indice++;
        }
    }
    //retornando o vetor de vizinhos
    return vizinhos;
}

//pegando peso da aresta
float pegaPesoAresta(Grafo* g, int v1, int v2) {
    if (!verifica_validade_vertice(g, v1) || !verifica_validade_vertice(g, v2)) {
        return -1.0;//retorna -1 se qlqr um dos vertices for invalido
    }
    return g->matriz[v1][v2];
}
