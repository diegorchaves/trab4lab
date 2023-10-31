#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "mesa.h"
#include "grupo.h"


void menu (Grupo *listaGrupos, Mesa *vetorMesas, int linhas, int colunas, Fila *filaEspera, Pilha **pilhaPratos)
{
    while (1)
    {
        int opcao;
        printf ("1) Chegar grupo\n2) Liberar mesa\n3) Sair da fila\n4) Imprimir pratos\n5) Imprimir fila\n6) Repor pratos\n7) Imprimir todas mesas\n8) Imprimir uma mesa\n9) Sair\n");
        printf ("Digite a opcao desejada: ");
        scanf ("%d", &opcao);
        switch (opcao)
        {
            case 1:
                listaGrupos = addGrupo (listaGrupos, vetorMesas, linhas, colunas, filaEspera, *pilhaPratos);
                break;
            case 2:
                listaGrupos = liberarMesa(listaGrupos, vetorMesas, linhas, colunas, filaEspera, *pilhaPratos);
                break;
            case 3:
                filaEspera = sairDaFila(filaEspera, listaGrupos);
                break;
            case 4:
                contaPratos(*pilhaPratos);
                break;
            case 5:
                filaImprime(filaEspera);
                break;
            case 6:
                reporPratos (*pilhaPratos);
                break;
            case 7:
                imprimeMesasTodas (vetorMesas, linhas, colunas);
                break;
            case 8:
                imprimeMesaEspecifica (vetorMesas, linhas, colunas);
                break;
            case 9:
                exit (1);
        }
    }
}

void liberaPrograma (Grupo *listaGrupos, Mesa *vetorMesas, Pilha *pilhaPratos, Fila *filaEspera)
{
    Grupo *p;
    for (p = listaGrupos; p != NULL; p = p->prox)
    {
        Grupo *next = p->prox;
        free (p);
        p = next;
    }

    free (pilhaPratos);
    free (vetorMesas);
    free (filaEspera);
}

int main ()
{
    /* vetor de mesas */
    Mesa *vetorMesas = NULL;

    /* lista que guarda os grupos */
    Grupo *listaGrupos = NULL;

    /* pilha que guarda pratos */
    Pilha *pilhaPratos = initPilha ();

    /* fila de espera */
    Fila *filaEspera = filaInicializa();

    /* perguntar ao usuario quantas linhas e colunas de mesas existem */
    int linhas, colunas;
    printf ("Informe o numero de linhas: ");
    scanf ("%d", &linhas);
    printf ("Informe o numero de colunas: ");
    scanf ("%d", &colunas);

    /* preencher fila de pratos*/
    pilhaPratos = pratoInicializa(pilhaPratos, linhas, colunas);

    /* alocar dinamicamente as mesas */
    vetorMesas = alocaMesas (linhas, colunas, pilhaPratos);

    /* menu */
    menu (listaGrupos, vetorMesas, linhas, colunas, filaEspera, &pilhaPratos);

    liberaPrograma (listaGrupos, vetorMesas, pilhaPratos, filaEspera);
}
