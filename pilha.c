#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "mesa.h"
#define LIV 0
#define OCP 1

void push (Pilha *pilha)
{
    Prato* novo = (Prato*)malloc(sizeof(Prato));
    novo->prox = pilha->prim;
    pilha->prim = novo;
}

void pop (Pilha *pilha)
{
    Prato* p = pilha->prim;

    if (p == NULL)
    {
        printf ("Pilha vazia.\n");
    }
    else
    {
        pilha->prim = p->prox;
        free (p);
    }
}

void reporPratos (Pilha *pilha)
{
    int quantidadeLocal;
    printf ("Digite quantos pratos deseja repor: ");
    scanf ("%d", &quantidadeLocal);
    for (int i = 0; i < quantidadeLocal; i++)
    {
        push (pilha);
    }
}

Pilha* pratoInicializa(Pilha *pilhaPratos, int linhas, int colunas)
{
    int quantidadePratos = linhas * colunas * 4;

    for(int i = 0; i < quantidadePratos; i++){
        push(pilhaPratos);
    }

    return pilhaPratos;
}

void contaPratos (Pilha *pil)
{
    Prato *p;
    int contador = 0;
    for (p = pil->prim; p != NULL; p = p->prox)
    {
        contador++;
    }
    printf ("Existem %d pratos na pilha.\n", contador);
}

void retiraPratosExcedentes (Pilha *pilha, int quantidadeMembros)
{
    int quantidadeAlterar = 4 - quantidadeMembros;

    for (int i = 0; i < quantidadeAlterar; i++)
    {
        push (pilha);
    }
}

void colocaPratosFaltam (Pilha *pilha, int quantidadeMembros)
{
    int quantidadeAlterar = 4 - quantidadeMembros;

    for (int i = 0; i < quantidadeAlterar; i++)
    {
        pop (pilha);
    }
}

Pilha *initPilha ()
{
    Pilha *new = (Pilha*)malloc(sizeof(Pilha));
    if (new == NULL)
    {
        printf ("Falha ao alocar.\n");
        exit (1);
    }
    new->prim = NULL;
    return new;
}