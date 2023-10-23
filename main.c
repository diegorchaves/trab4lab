#include <stdio.h>
#include <stdlib.h>
#include "mesa.h"
#include "grupo.h"
#define OCP 0
#define LIV 1


void menu ()
{
    printf("+-----------------------------+-");
    printf("------------------------------------+\n");
    printf("|1 - Chegar grupo             | ");
    printf("6 - Imprimir pilha de pratos        |\n");
    printf("|2 - Liberar mesa             | ");
    printf("7 - Imprimir fila de espera         |\n");
    printf("|3 - Sair da fila             | ");
    printf("8 - Imprimir ocupacao               |\n");
    printf("|4 - Arrumar mesa             | ");
    printf("9 - Sair                            |\n");
    printf("|5 - Repor pratos             | ");
    printf("                                    |\n");
    printf("+-----------------------------+-");
    printf("------------------------------------+\n");
}

void leOpcaoMenu (int index, Mesa* vetorMesas, int qtdLinhas, int qtdColunas, Grupo *fila)
{

    switch (index)
    {
        case 1:
            chegaGrupo(vetorMesas, fila, qtdLinhas, qtdColunas);
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:

            break;
        case 5:
            
            break;
        case 6:

            break;
        case 7:

            break;
        case 8:
            imprimeMesasLivres(vetorMesas, qtdLinhas, qtdColunas);
            break;
        case 9:

            break;
        default:
            break;
    }
}


int perguntaLinhasColunas(int *qtdLinhas, int *qtdColunas)
{

    printf ("Informe linhas: ");
    scanf ("%d", qtdLinhas);
    printf ("Informe colunas: ");
    scanf ("%d", qtdColunas);

    return *qtdLinhas * *qtdColunas;
}   



int main ()
{
    int qtdMesas, qtdLinhas, qtdColunas, index;
    
    Mesa *vetorMesas;
    
    qtdMesas = perguntaLinhasColunas(&qtdLinhas, &qtdColunas);

    vetorMesas = alocaVetor(qtdMesas);
    setaMesasIniciais(vetorMesas, qtdLinhas, qtdColunas);

    Grupo *fila = NULL;
    do
    {
        menu();
        scanf("%d", &index);
        leOpcaoMenu(index, vetorMesas, qtdLinhas, qtdColunas, fila);
        
    } while(1);
    
    
    
}