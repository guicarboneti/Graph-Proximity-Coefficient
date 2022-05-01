O programa teste.c lê um grafo da entrada padrão (stdin) e calcula o coeficiente de proximidade de um vértice no grafo dado.

Para a implementação, foram criadas duas estruturas para armazenar os vértices e o grafo:
    * A estrutura do vértice possui 5 campos: uma string nome, três inteiros para amazenar o número de vizinhos, a distância e o estado do vértice e um ponteiro para um vetor de vértices vizinhos;
    * Já a estrutura do grafo possui um inteiro n para armazenar o número de vértices no grafo e um ponteiro para um vetor de vértices que representa o grafo.
Ainda, alteramos a declaração da função le_vertice em grafo.h para que ela receba um grafo como parâmetro e a implementamos de forma que ela leia o nome de um vértice em stdin e retorne um ponteiro para o vértice correspondente no grafo do parâmetro.
Também, implementamos uma fila de vértices e suas funções de manipulação que foram utilizadas no cálculo do coeficiente.

Para a leitura e o cálculo do coeficiente, teste.c utiliza as funções declaradas no arquivo de header grafo.h e implementadas em grafo.c.
Para executar o programa, é necessário rodar o comando './teste' e digitar o grafo a ser calculado no seguinte formato:

a b
b c
c d
d e

Onde cada linha representa uma aresta entre o primeiro vértice e o segundo vértice.
Uma linha com apenas um vértice representa um vértice isolado.

Após declarar todos os vértices e arestas, é necessário digitar CTRL+D para encerrar a leitura do grafo.
Por fim, informe o vértice que se deseja calcular o coeficiente de proximidade.
