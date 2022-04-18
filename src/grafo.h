#ifndef _GRAFO_H
#define _GRAFO_H

#define TAMANHO 10

#include <stdio.h>

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
// 
// o vértice tem um nome, que é uma "string"

typedef struct vertice vertice;
struct vertice {
  char nome[TAMANHO];
  vertice** vizinhos;
  vertice* pai;
  int estado;
  int distancia;
  int numVizinhos;
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo tem um nome, que é uma "string"

typedef struct grafo grafo;
struct grafo {
  char nome[TAMANHO];
  vertice** v;
  int n;
};

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroi_grafo(grafo g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
// 
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

grafo le_grafo(FILE *input);  



//------------------------------------------------------------------------------
// pede para o usuário entrar com um vértice.

vertice *le_vertice(grafo *g);


//------------------------------------------------------------------------------
// encontra o menor caminho entre cada par do vértice v de g
// 

void caminhos_minimos(vertice *v);


//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
// 

double coeficiente_proximidade(grafo g, vertice *v);


//------------------------------------------------------------------------------
// imprime grafo

void imprimeGrafo(grafo g);


struct Fila {
	int capacidade;
	vertice **v;
	int primeiro;
	int ultimo;
	int n;
};

void criarFila( struct Fila *f, int c );

void inserir(struct Fila *f, vertice *v);  // insere no final

vertice *remover( struct Fila *f );  // pega o item do começo da fila

int estaVazia( struct Fila *f );  // retorna verdadeiro se a fila está vazia

void printFila(struct Fila *fila);

#endif
