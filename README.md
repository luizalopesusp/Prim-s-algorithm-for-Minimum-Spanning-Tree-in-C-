🇺🇸 English
About

This project was developed as Programming Exercise 1 (EP1) for the course ACH2024 — Algorithms and Data Structures II at the University of São Paulo (USP), 2026.

The program implements Prim's algorithm to compute the Minimum Spanning Tree (MST) of a weighted undirected graph, using a binary min-heap as the priority queue. The context is a fiber optic network connecting factory servers — the MST represents the lowest-cost cabling layout that keeps all units connected.

How It Works

The graph is read from a .txt input file and can be represented in two ways, chosen at compile time via preprocessor directives:

Adjacency Matrix (grafo_matrizadj.c) — better for dense graphs
Adjacency List (grafo_listaadj.c) — better for sparse graphs

The main file (ep1_12822076.c) is implementation-agnostic: it only uses the interface defined in grafo.h, making the code modular and extensible.

Algorithm flow:

Read graph from file
       ↓
Validate edges (invalid vertices, self-loops,
parallel edges, invalid weights)
       ↓
Check connectivity
       ↓
Run Prim's algorithm with min-heap
       ↓
Write MST to output file
Input Validation

The program detects and reports all of the following errors:

Error	Description
ERRO: VERTICE INVALIDO	Vertex number is negative or out of range
ERRO: AUTO-LACO	Edge connecting a vertex to itself
ERRO: ARESTA PARALELA	Duplicate edge between two vertices
ERRO: PESO INVALIDO	Edge weight is zero or negative
ERRO: GRAFO NAO CONECTADO	Graph is disconnected — MST cannot be computed
Project Structure
ep1_12822076.c       ← main file: Prim's algorithm + min-heap + graph reading
grafo.h              ← interface header (shared by both implementations)
grafo_listaadj.c     ← adjacency list implementation
grafo_matrizadj.c    ← adjacency matrix implementation
entrada_1.txt        ← sample input: valid connected graph (6 vertices, 10 edges)
entrada_2.txt        ← sample input: graph with multiple errors
entrada_3.txt        ← sample input: disconnected graph
entrada_4.txt        ← sample input: mixed invalid edges
saida_1.txt          ← expected output for entrada_1.txt
saida_2.txt          ← expected output for entrada_2.txt
saida_3.txt          ← expected output for entrada_3.txt
assignment.pdf       ← original assignment
Requirements
GCC compiler
Linux terminal (or Windows CMD)
-lm flag required (math library)
How to Compile

With adjacency list:

bash
gcc -o ep1_12822076 ep1_12822076.c -lm

With adjacency matrix:

bash
gcc -DMATRIZ -o ep1_12822076 ep1_12822076.c -lm
How to Run
bash
./ep1_12822076 <input_file.txt> <output_file.txt>
Example

Using entrada_1.txt (6 vertices, 10 edges):

6 10
0 1 6.3
0 2 1.7
...

Expected output (saida_1.txt):

14.5
4
0 2 1.7
1 2 2.9
2 3 2.6
3 5 4.2
4 5 3.1

The output shows the total MST cost, the farthest vertex from the origin, and each edge of the MST sorted by source vertex.

🇧🇷 Português
Sobre

Este projeto foi desenvolvido como Exercício de Programação 1 (EP1) da disciplina ACH2024 — Algoritmos e Estruturas de Dados II da Universidade de São Paulo (USP), 2026.

O programa implementa o algoritmo de Prim para calcular a Árvore Geradora Mínima (AGM) de um grafo não direcionado ponderado, utilizando um heap binário mínimo como fila de prioridade. O contexto é uma rede de fibra óptica conectando servidores de fábricas — a AGM representa o cabeamento de menor custo que mantém todas as unidades conectadas.

Como Funciona

O grafo é lido de um arquivo .txt de entrada e pode ser representado de duas formas, escolhidas em tempo de compilação via diretivas de pré-processador:

Matriz de Adjacência (grafo_matrizadj.c) — melhor para grafos densos
Lista de Adjacência (grafo_listaadj.c) — melhor para grafos esparsos

O arquivo principal (ep1_12822076.c) é independente da implementação: utiliza apenas a interface definida em grafo.h, tornando o código modular e extensível.

Fluxo do algoritmo:

Leitura do grafo do arquivo
       ↓
Validação das arestas (vértices inválidos, auto-laços,
arestas paralelas, pesos inválidos)
       ↓
Verificação de conectividade
       ↓
Execução do algoritmo de Prim com min-heap
       ↓
Escrita da AGM no arquivo de saída
Validação de Entrada

O programa detecta e reporta todos os seguintes erros:

Erro	Descrição
ERRO: VERTICE INVALIDO	Número do vértice é negativo ou fora do intervalo
ERRO: AUTO-LACO	Aresta conectando um vértice a si mesmo
ERRO: ARESTA PARALELA	Aresta duplicada entre dois vértices
ERRO: PESO INVALIDO	Peso da aresta é zero ou negativo
ERRO: GRAFO NAO CONECTADO	Grafo desconexo — AGM não pode ser calculada
Estrutura do Projeto
ep1_12822076.c       ← arquivo principal: algoritmo de Prim + min-heap + leitura do grafo
grafo.h              ← cabeçalho da interface (compartilhado pelas duas implementações)
grafo_listaadj.c     ← implementação por lista de adjacência
grafo_matrizadj.c    ← implementação por matriz de adjacência
entrada_1.txt        ← entrada de exemplo: grafo válido e conectado (6 vértices, 10 arestas)
entrada_2.txt        ← entrada de exemplo: grafo com múltiplos erros
entrada_3.txt        ← entrada de exemplo: grafo desconexo
entrada_4.txt        ← entrada de exemplo: arestas inválidas mistas
saida_1.txt          ← saída esperada para entrada_1.txt
saida_2.txt          ← saída esperada para entrada_2.txt
saida_3.txt          ← saída esperada para entrada_3.txt
assignment.pdf       ← enunciado original
Requisitos
Compilador GCC
Terminal Linux (ou CMD do Windows)
Flag -lm obrigatória (biblioteca matemática)
Como Compilar

Com lista de adjacência:

bash
gcc -o ep1_12822076 ep1_12822076.c -lm

Com matriz de adjacência:

bash
gcc -DMATRIZ -o ep1_12822076 ep1_12822076.c -lm
Como Executar
bash
./ep1_12822076 <arquivo_entrada.txt> <arquivo_saida.txt>
Exemplo

Usando entrada_1.txt (6 vértices, 10 arestas):

6 10
0 1 6.3
0 2 1.7
...

Saída esperada (saida_1.txt):

14.5
4
0 2 1.7
1 2 2.9
2 3 2.6
3 5 4.2
4 5 3.1

A saída mostra o custo total da AGM, o vértice mais distante da origem e cada aresta da AGM ordenada por vértice de origem.

Developed by Luiza de Jesus Lopes — USP nº 12822076
