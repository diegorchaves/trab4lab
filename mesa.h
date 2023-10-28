#include <stdio.h>

typedef struct mesa
{
    int numero;
    int ocupada;
    int quantidadeSentada;
    int numeroComanda;
} Mesa;


Mesa *alocaMesas (int linhas, int colunas, Pilha *pilha);

int existeMesaLivre (Mesa *vetor, int linhas, int colunas);

Mesa *atribuiMesa (Mesa *vetor, int linhas, int colunas, int quantidadeMembros, Pilha *pilha);

void imprimeMesasTodas (Mesa *vetor, int linhas, int colunas);

void imprimeMesaEspecifica (Mesa *vetor, int linhas, int colunas);

void imprimeMesasLivres (Mesa *vetor, int linhas, int colunas);
