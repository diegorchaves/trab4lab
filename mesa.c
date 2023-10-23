#include <stdlib.h>
#include <stdio.h>
#include "mesa.h"
#define OCP 0
#define LIV 1


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

void imprimeMesasLivres(Mesa *vetorMesas, int qtdLinhas, int qtdColunas)
{
    for (int i = 0; i < qtdLinhas; i++)
    {
        {
            for (int j = 0; j < qtdColunas; j++)
            {   
                if(vetorMesas[i*qtdColunas+j].livre == LIV){
                    int numeroMesa = i*qtdColunas+j+1;
                    printf("Mesa %d livre\n", numeroMesa);
                }
            }
        }
    }
}