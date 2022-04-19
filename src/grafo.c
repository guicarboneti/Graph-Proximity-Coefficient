#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"
// #include "fila.h"

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroi_grafo(grafo g) {
  free(g.v);
  return g.v == NULL;
}

/*
Retorna ponteiro para vértice buscado em v(g). Se não estiver incluso, retorna null.
*/
int busca(grafo* g, char* palavra) {
  int i = 0;
  while ((i < g->n) && (strcmp(g->v[i]->nome, palavra) != 0))
    i++;
  
  return i;
}

/*
Se o vértice não estiver em v(g), o insere
*/
void trataVertice(grafo* g, char* palavra) {
  if (busca(g, palavra) == g->n) {
    vertice* novo = (vertice*)malloc(sizeof(vertice*));
    strcpy(novo->nome, palavra);
    novo->numVizinhos = 0;
    novo->estado=0;
    novo->distancia=0;
    novo->vizinhos = (vertice**)calloc(50, sizeof(vertice*));
    g->v[g->n] = novo;
    g->n++;
  }
}

void trataVizinho(grafo* g, char* vert, char* vizinho) {
  // Insere vizinho no v(g), se já não estiver
  trataVertice(g, vizinho);
  vertice* viz = g->v[busca(g, vizinho)];

  // Insere vizinho na lista de vizinhos do vértice
  vertice* ve = g->v[busca(g, vert)];

  ve->vizinhos[ve->numVizinhos] = viz;
  ve->numVizinhos++;

  if (ve->numVizinhos % 50 == 0) {
    ve->vizinhos = realloc(ve->vizinhos, ve->numVizinhos+50);
  }
  
  viz->vizinhos[viz->numVizinhos] = ve;
  viz->numVizinhos++;

  if (viz->numVizinhos % 50 == 0) {
    viz->vizinhos = realloc(viz->vizinhos, viz->numVizinhos+50);
  }
}

//------------------------------------------------------------------------------
// lê um grafo
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo le_grafo(FILE *input) {
  // grafo *g = (grafo*)malloc(sizeof(grafo));
  grafo g;
  g.n = 0;
  g.v = (vertice**)calloc(50, sizeof(vertice*));

  printf("Digite o nome do grafo:\n");
  scanf("%s", g.nome);

  // Leitura
  printf("Digite os vértices de %s:\n", g.nome);

  int cont = 0, tammax = 50;
  char linha[TAMANHO];

  fgets((char *)linha, TAMANHO, input);
  while (!feof(input)) {
    linha[strcspn(linha, "\n")] = '\0';
    if (!(linha[0] == '\0')) {
      // Trata linha de entrada
      char vert[TAMANHO];
      char viz[TAMANHO];
      
      strncpy(vert, linha, strcspn(linha, " "));
      trataVertice(&g, vert);
      if (strcmp(linha, vert) != 0) {
        strncpy(viz, linha+strcspn(linha, " ")+1, strcspn(linha, "\0"));
        trataVizinho(&g, vert, viz);
      }

      cont++;
      // Realloc a cada 50 entradas
      if ((cont > 0) && (cont % tammax == 0)) {
        tammax+=50;
        g.v = realloc(g.v, tammax * sizeof(vertice**));
      }
    }
    fgets((char *)linha, TAMANHO, input);
  }

  if (input == stdin)
    clearerr(input);

  return g;
}


//------------------------------------------------------------------------------
// lê um vertice e retorna um ponteiro para ele

vertice *le_vertice(grafo g) {
  int i;
  vertice* v;
  char nome[TAMANHO];
  printf("Digite o nome do vértice:\n");
  scanf("%s", nome);
  for (i=0; i<g.n; i++)
    if (strcmp(g.v[i]->nome, nome)==0)
      v = g.v[i];

  return v;
}

void imprimeGrafo(grafo g) {
  for (int i = 0; i < g.n; i++) {
    printf("%s: ", g.v[i]->nome);
    for (int j = 0; j < g.v[i]->numVizinhos; j++)
      printf("%s ", g.v[i]->vizinhos[j]->nome);
    printf("\n");
  }
}

void printFila(struct Fila *fila) {
  int cont, i;
	for ( cont=0, i= fila->primeiro; cont < fila->n; cont++){
		printf("%s - ",fila->v[i++]->nome);
		if (i == fila->capacidade)
			i=0;
	}
	printf("\n\n");
}

//------------------------------------------------------------------------------
// encontra o menor caminho entre cada par do vértice v de g
// 

void caminhos_minimos(vertice *raiz) {
  int i;
  struct Fila fila;
  vertice *v;
  criarFila(&fila, 10);
  raiz->distancia = 0;
  raiz->estado = 1;
  inserir(&fila, raiz);

  for (; !estaVazia(&fila) ;) {
    v = remover(&fila);
    for (i=0; i<v->numVizinhos; i++) {
      if (v->vizinhos[i]->estado==0) {
        v->vizinhos[i]->distancia = v->distancia + 1;   // distancia do pai + 1
        inserir(&fila, v->vizinhos[i]);
        v->vizinhos[i]->estado = 1;
      }
    }
    v->estado = 2;
  }
}

//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
// 

double coeficiente_proximidade(grafo g, vertice *v) {

  int somaDistVizinhos=0;
  int i,j;
  caminhos_minimos(v);
  for (i=0; i<g.n; i++) {
    if (strcmp(v->nome, g.v[i]->nome) != 0)
      somaDistVizinhos += g.v[i]->distancia;
  }
  double Cp = (double) g.n / (double) somaDistVizinhos;
  return Cp;
}

void criarFila( struct Fila *f, int c ) { 
	f->capacidade = c;
	f->v = (vertice**) malloc(f->capacidade * sizeof(vertice*));
	f->primeiro = 0;
	f->ultimo = -1;
	f->n = 0; 
}

void inserir(struct Fila *f, vertice *v) {   // insere no final
	if(f->ultimo == f->capacidade-1)
		f->ultimo = -1;

	f->ultimo++;
	f->v[f->ultimo] = v; // incrementa ultimo e insere
	f->n++; // mais um item inserido
}

vertice *remover( struct Fila *f ) { // pega o item do começo da fila
	vertice *temp = f->v[f->primeiro++]; // pega o valor e incrementa o primeiro

	if(f->primeiro == f->capacidade)
		f->primeiro = 0;

	f->n--;  // um item retirado
	return temp;
}

int estaVazia( struct Fila *f ) { // retorna verdadeiro se a fila está vazia
	return (f->n==0);
}
