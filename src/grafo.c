#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"

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
    novo->vizinhos = (vertice**)calloc(50, sizeof(vertice*));
    novo->numVizinhos = 0;
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
// lê um vertice 

vertice le_vertice() {
  vertice v;
  printf("Digite o nome do vértice:\n");
  scanf("%s", v.nome);

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



//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
// 

double coeficiente_proximidade(grafo g, vertice v) {
  return 0;
}

