#ifndef _GRAFO_H
#define _GRAFO_H

#include "grafo.h"

struct Fila {
	int capacidade;
	vertice *v;
	int primeiro;
	int ultimo;
	int n;
};

void criarFila( struct Fila *f, int c );

void inserir(struct Fila *f, vertice v);  // insere no final

vertice *remover( struct Fila *f );  // pega o item do começo da fila

int estaVazia( struct Fila *f );  // retorna verdadeiro se a fila está vazia

#endif