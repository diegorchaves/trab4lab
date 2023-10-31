#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "mesa.h"
#define LIV 0
#define OCP 1

Mesa *alocaMesas (int linhas, int colunas, Pilha *pilha)
{
    /* alocando dinamicamente */
    Mesa *vetor = (Mesa*)malloc(sizeof(Mesa) * linhas * colunas);
    if (vetor == NULL)
    {
        printf ("Falha de alocacao. O programa sera encerrado.\n");
        exit (1);
    }

    /* setando as mesas */
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {   
            for(int k = 0; k < 4; k++){
                pop(pilha);
            }
            vetor[i * colunas + j].numero = i * colunas + j + 1;
            vetor[i * colunas + j].numeroComanda = i * colunas + j;
            vetor[i * colunas + j].ocupada = LIV;
            vetor[i * colunas + j].quantidadeSentada = 0;
        }
    }

    return vetor;
}

int existeMesaLivre (Mesa *vetor, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor[i * colunas + j].ocupada == LIV)
            {
                return 1;
            }
        }
    }
    return 0;
}

Mesa *atribuiMesa (Mesa *vetor, int linhas, int colunas, int quantidadeMembros, Pilha *pilha)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor[i * colunas + j].ocupada == LIV)
            {
                printf ("Mesa %d designada.\n", vetor [i * colunas + j].numero);
                vetor[i * colunas + j].ocupada = OCP;
                vetor[i * colunas + j].quantidadeSentada = quantidadeMembros;
                retiraPratosExcedentes (pilha, quantidadeMembros);
                return &vetor[i * colunas + j];
            }
        }
    }
    printf ("Nao existem mesas disponiveis, o(s) grupo(s) ficara(o) na fila de espera.\n");
    return NULL;
}

void imprimeMesasTodas (Mesa *vetor, int linhas, int colunas)
{
    printf("\nImprimindo mesas...\n");

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor [i * colunas + j].ocupada == OCP)
            {
                printf ("Mesa %d tem %d sentados.\n", vetor [i * colunas + j].numero, vetor [i * colunas + j].quantidadeSentada);
            }
        }
    }
}

void imprimeMesaEspecifica (Mesa *vetor, int linhas, int colunas)
{
    int numeroLocal;
    printf ("Digite o numero da mesa: ");
    scanf ("%d", &numeroLocal);

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor [i * colunas + j].numero == numeroLocal)
            {
                printf ("Mesa %d tem %d sentados.\n", vetor [i * colunas + j].numero, vetor [i * colunas + j].quantidadeSentada);
                return;
            }
        }
    }
    printf ("Mesa de numero %d nao encontrada.\n", numeroLocal);
}

void imprimeMesasLivres (Mesa *vetor, int linhas, int colunas)
{   
    printf("\nImprimindo mesas livres...\n");
    if(!existeMesaLivre(vetor, linhas, colunas)){
        printf("Nenhuma mesa livre\n");
        return;
    }

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor[i * colunas + j].ocupada == LIV)
            {
                printf ("Mesa %d livre.\n", vetor [i * colunas + j].numero);
            }
        }
    }
    
}
