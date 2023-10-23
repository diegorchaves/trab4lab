#include <stdlib.h>

typedef struct mesa
{
    int numeroMesa;
    int livre;
    int qtdPessoasSentadas;
    int numeroComanda;
} Mesa;


Mesa *alocaVetor (int qtdMesas);

void setaMesasIniciais (Mesa *vetorMesas, int qtdLinhas, int qtdColunas);

void imprimeMesasLivres(Mesa *vetorMesas, int qtdLinhas, int qtdColunas);