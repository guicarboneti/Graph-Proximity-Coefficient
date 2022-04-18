#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

void criarFila( struct Fila *f, int c ) { 
	f->capacidade = c;
	f->v = (vertice*) malloc (f->capacidade * sizeof(vertice));
	f->primeiro = 0;
	f->ultimo = -1;
	f->n = 0; 
}

void inserir(struct Fila *f, vertice v) {   // insere no final
	if(f->ultimo == f->capacidade-1)
		f->ultimo = -1;

	f->ultimo++;
	f->v[f->ultimo] = v; // incrementa ultimo e insere
	f->n++; // mais um item inserido
}

vertice *remover( struct Fila *f ) { // pega o item do começo da fila
	vertice *temp = &f->v[f->primeiro++]; // pega o valor e incrementa o primeiro

	if(f->primeiro == f->capacidade)
		f->primeiro = 0;

	f->n--;  // um item retirado
	return temp;
}

int estaVazia( struct Fila *f ) {   // retorna verdadeiro se a fila está vazia
	return (f->n==0);
}