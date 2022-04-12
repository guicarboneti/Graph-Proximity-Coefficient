#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {
  grafo g;
  vertice v;
  double coef;

  g = le_grafo(stdin);
  v = le_vertice();

  if ( &g == NULL )
    return 1;

  coef = coeficiente_proximidade(g,v);

  printf ("O coeficiente de proximidade é %f\n", coef);
  imprimeGrafo(g);

  return ! destroi_grafo(g);
}
