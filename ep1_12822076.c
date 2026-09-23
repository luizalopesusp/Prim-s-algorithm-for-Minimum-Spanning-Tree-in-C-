#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#ifdef MATRIZ
#include "grafo_matrizadj.c"
#else
#include "grafo_listaadj.c"
#endif

//estrutura do min-heap
typedef struct{
    int vertice;
    float custo;
    int origem;
}Itemheap;

//estrutura da fila
typedef struct{
    Itemheap* vetor;
    int tamanho;
    int capacidade;
}Minheap;

//estrutura para ordenar as arestas
typedef struct{
    int u;
    int v;
    float peso;
}Aresta__AGM;

//função auxiliar para trocar dois de lugar dentro do vetor
void troca (Itemheap* item1, Itemheap *item2){
    Itemheap aux = *item1;
    *item1 = *item2;
    *item2 = aux;
}

//subindo no heap
void sobeNoHeap(Minheap* h, int indice){
    int item_pai = (indice -1)/2;
    //enquanto não chega na raiz e o custo atual do item é menor que o do pai
    while(indice > 0 && h->vetor[indice].custo < h->vetor[item_pai].custo){
        //trocando de lugar
        troca(&h->vetor[indice], &h->vetor[item_pai]);

        //atualiza indice e calcula o novo pai
        indice = item_pai;
        item_pai = (indice - 1)/2;
    }
}

//inserindo elemento no heap
void insereHeap(Minheap* h, int vertice, float custo, int origem){
    if(h->tamanho >= h->capacidade){
        printf("ERRO: O heap está cheio\n");
        return;
    }

    //insere novo item na primeira posição vazia
    int i = h->tamanho;
    h->vetor[i].vertice = vertice;
    h->vetor[i].custo = custo;
    h->vetor[i].origem = origem;
    //incrementa cont de elementos
    h->tamanho++;
    //chamando a operação sobeNoHeap para o novo elemento inserido
    sobeNoHeap(h,i);
}

//operação para heapfy down
void desceNoHeap(Minheap* h, int indice){
    int menor = indice;
    int esq = 2*indice+1;
    int dir = 2*indice+2;

    //se o filho da esquerda existir e for mais barato que o pai, entao o menor agora é esquerda
    if(esq < h->tamanho && h->vetor[esq].custo < h->vetor[menor].custo){
        menor = esq;
    }
    //se o filho da direita existir no vetor e for mais barato que o menor até agora
    if(dir < h->tamanho && h->vetor[dir].custo < h->vetor[menor].custo){
        menor = dir;
    }

    if(menor != indice){
        troca(&h->vetor[indice], &h->vetor[menor]);
        desceNoHeap(h,menor);
    }
}

Itemheap extraiMinimo (Minheap* h){
    //em caso do heap estar vazio
    if(h->tamanho == 0){
        Itemheap vazio = {-1,-1.0,-1};
        return vazio;
    }
    Itemheap minimo = h->vetor[0];

    //raiz pega o ultimo elemento do vetor
    h->vetor[0] = h->vetor[h->tamanho - 1];
    h->tamanho--;

    desceNoHeap(h,0);

    return minimo;
}

//inicializando heap
Minheap* inicializaHeap(int capacidade){
    Minheap* h = (Minheap*) malloc(sizeof(Minheap));
    h->vetor = (Itemheap*) malloc(capacidade*sizeof(Itemheap));
    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

//liberando memoria do heap
void liberaHeap(Minheap* h) {
    if (h != NULL) {
        free(h->vetor);
        free(h);
    }
}

//verificando se heap está vazio
bool heapVazio(Minheap* h) {
    return h->tamanho == 0;
}

//algoritmo de prim pra fazer a arvore geradora minima e verifica se o grafo é conexo ou não
void Prim(Grafo* g, int numV) {
    if (g == NULL || numV <= 0) return;

    //alocando memoria para o vetor que guarda os vertices visitados
    bool* visitados = (bool*) calloc(numV, sizeof(bool));
    //garantindo que vai ter espaço pra arestas duplicadas em grafo denso
    Minheap* h = inicializaHeap(numV * numV * 5);
    
    float custo_agm = 0.0;
    int contag_vertices_visitados = 0;

    //guardando as arestas na AGM
    Aresta__AGM* arestas_resultado = (Aresta__AGM*) malloc((numV - 1)*sizeof(Aresta__AGM));
    int numArestas = 0;

    // Começamos pelo vértice 0 com custo 0
    insereHeap(h, 0, 0.0, -1);

    //extraindo o vertice mais barato
    while (!heapVazio(h)) {
        Itemheap atual = extraiMinimo(h);//ta extraindo a conexao mais barata ate agoar

        //não faz nada se ja foi visitado
        if (visitados[atual.vertice]) {
            continue;
        }
        //muda flag pra true e incrementa contagem de vertices visitados
        visitados[atual.vertice] = true;
        contag_vertices_visitados++;

        if (atual.origem != -1) {
            //
            arestas_resultado[numArestas].u = (atual.origem < atual.vertice) ? atual.origem : atual.vertice;
            arestas_resultado[numArestas].v = (atual.origem > atual.vertice) ? atual.origem : atual.vertice;
            arestas_resultado[numArestas].peso = atual.custo;
            numArestas++;
            custo_agm += atual.custo;
        }

        //pegando os vizinhos do não-visitado
        int numVizinhos;
        int* vizinhos = pegaVizinhos(g, atual.vertice, &numVizinhos);

        if (vizinhos != NULL) {
            for (int i = 0; i < numVizinhos; i++) {
                int vizinho = vizinhos[i];
                if (!visitados[vizinho]) {
                    //pegando o peso da aresta para inserir no heap
                    float peso = pegaPesoAresta(g, atual.vertice, vizinho);
                    insereHeap(h, vizinho, peso, atual.vertice);
                }
            }
            //liberando memoria
            free(vizinhos);
        }
    }

    //se o total de vertices visitados for diferente do total de vertices no grafo
    if (contag_vertices_visitados != numV) {
        //entao o grafo não é conectado
        printf("ERRO: GRAFO NAO CONECTADO\n");
    } else {//utilizando bubblesort pra ordenar a saida
        for (int i = 0; i < numArestas - 1; i++) {
            for (int j = 0; j < numArestas - i - 1; j++) {
                if (arestas_resultado[j].u > arestas_resultado[j+1].u || 
                   (arestas_resultado[j].u == arestas_resultado[j+1].u && arestas_resultado[j].v > arestas_resultado[j+1].v)) {
                    Aresta__AGM temp = arestas_resultado[j];
                    arestas_resultado[j] = arestas_resultado[j+1];
                    arestas_resultado[j+1] = temp;
                }
            }
        }
        //imprimindo um de cada vez
        printf("%.1f\n", custo_agm);
        for(int i = 0; i < numArestas; i++){
            printf("%d %d %.1f\n", arestas_resultado[i].u, arestas_resultado[i].v, arestas_resultado[i].peso);
        }

    }

    //liberando memoria do vetor de visitados e do resultado
    free(arestas_resultado);
    free(visitados);
    //liberando memoria da estrutura do heap
    liberaHeap(h);
}

//lendo o grafo passado em arquivo de entrada
bool le_grafo(const char* arq_entr, Grafo** grafo, int* numVlidos) {
    //abrindo o arquivo de entrada
    FILE* arq_entrada = fopen(arq_entr, "r");
    if (arq_entrada == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de entrada (%s)\n", arq_entr);
        return false;
    }

    int numV, numA;
    //lendo a primeira linha com as quantidades de aretas e vertices
    if (fscanf(arq_entrada, "%d %d", &numV, &numA) != 2) {
        fclose(arq_entrada);
        return false;
    }

    //checando maximo de vertices
    if(numV > MAXNUMVERTICES){
        printf("ERRO: O Grafo possui mais de 100 vértices\n");
        fclose(arq_entrada);
        return false;
    }

    //pegando o numero de vertices
    *numVlidos = numV;

    //inicializando grafo
    Grafo* g = inicializaGrafo(numV);
    if (g == NULL) {
        fclose(arq_entrada);
        return false;
    }
    *grafo = g;

    //lendo as linhas das aretas
    int v1, v2;
    float peso;
    for (int i = 0; i < numA; i++) {
        if (fscanf(arq_entrada, "%d %d %f", &v1, &v2, &peso) == 3) {
            insereAresta(g, v1, v2, peso);
        } else {
            // Se vier uma linha torta, limpamos o buffer para tentar a próxima
            fscanf(arq_entrada, "%*[^\n]");
        }
    }
    //fechando o arquivo de entrada
    fclose(arq_entrada);
    return true;
}

int main(int argc, char* argv[]){
    //verifica se a linha de comando está correta
    if(argc < 3){
        printf("Comando errado. Formato deve ser: %s <arquivo_entrada> <arquivo_saida>\n",argv[0]);
        return 1;
    }
    if(freopen(argv[2],"w",stdout) == NULL){
        perror("Erro ao criar arquivo de saída");
        return 1;
    }

    //lendo o grafo
    Grafo* g = NULL;
    int numVertices = 0;
    if(!le_grafo(argv[1], &g, &numVertices)){//tratamento caso a leitura falhe
        return 1;
    }

    //executando prim
    Prim(g, numVertices);

    liberaGrafo(g);

    return 0;
}