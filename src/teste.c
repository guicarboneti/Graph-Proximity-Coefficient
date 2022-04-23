#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {
  grafo g;
  vertice* v;
  double coef;

  g = le_grafo(stdin);
  v = le_vertice(g);
  if ( (&g == NULL) || (v == NULL) )
    return 1;

  coef = coeficiente_proximidade(g,v);
  printf ("\nO coeficiente de proximidade é %lf\n", coef);

  return destroi_grafo(g);
}
