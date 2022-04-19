#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {
  grafo g;
  vertice* v;
  double coef;

  g = le_grafo(stdin);
  // for (int i=0;i<g.n;i++)
  //   printf("--> %d %d %d\n", g.v[i]->estado, g.v[i]->distancia, g.v[i]->numVizinhos);
  v = le_vertice(g);
  // printf("estado: %d, dist: %d, numV: %d\n", v->estado, v->distancia, v->numVizinhos);
  if ( &g == NULL )
    return 1;

  coef = coeficiente_proximidade(g,v);

  printf ("O coeficiente de proximidade é %f\n", coef);
  imprimeGrafo(g);

  return ! destroi_grafo(g);
}
