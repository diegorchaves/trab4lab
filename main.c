#include <stdio.h>
#include <stdlib.h>
#define OCP 0
#define LIV 1

typedef struct mesa
{
    int numeroMesa;
    int livre;
    int qtdPessoasSentadas;
    int numeroComanda;
} Mesa;

typedef struct grupo
{
    int qtdPessoasGrupo;
    int idGrupo
} Grupo;

//  é possível usar uma lista de grupos, ao inserir ordenar por idGrupo.
//  ao chegar um grupo, se tiver mais que 4 pessoas, criar um segundo nó com as pessoas restantes.

Mesa *alocaVetor (int qtdMesas)
{
    Mesa *vetorAlocado = (Mesa*)malloc(sizeof(Mesa) * qtdMesas);
    return vetorAlocado;
}

void setaMesasIniciais (Mesa *vetorMesas, int qtdLinhas, int qtdColunas)
{
    for (int i = 0; i < qtdLinhas; i++)
    {
        {
            for (int j = 0; j < qtdColunas; j++)
            {
                vetorMesas[i*qtdColunas+j].livre = LIV;
                vetorMesas[i*qtdColunas+j].numeroComanda = i*qtdColunas+j+1;
                vetorMesas[i*qtdColunas+j].numeroMesa = i*qtdColunas+j+1;
                vetorMesas[i*qtdColunas+j].qtdPessoasSentadas = 0;
            }
        }
    }
}

int main ()
{
    int qtdLinhas, qtdColunas, qtdMesas;
    Mesa *vetorMesas;
    
    printf ("Informe linhas: ");
    scanf ("%d", &qtdLinhas);
    printf ("Informe colunas: ");
    scanf ("%d", &qtdColunas);
    qtdMesas = qtdLinhas * qtdColunas;

    vetorMesas = alocaVetor (qtdMesas);

    setaMesasIniciais (vetorMesas, qtdLinhas, qtdColunas);
}