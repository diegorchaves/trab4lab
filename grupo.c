#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "mesa.h"
#include "grupo.h"
#define LIV 0
#define OCP 1

Fila *filaInicializa()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;

    return f;
}

void filaInsere (Fila* filaEspera, Grupo *novo)
{
    
    if (filaEspera->fim != NULL){
        filaEspera->fim->prox = novo;
    } else{
        filaEspera->ini = novo;
    }
    filaEspera->fim = novo; 

}

void filaImprime(Fila* f)
{
    Grupo* q;
    int posicao = 1, totalNaFila = 0;

    if(f->ini == NULL){
        printf("\nFila de espera vazia\n");
        return;
    }

    printf("\nImprimindo fila de espera...\n");
    for(q = f->ini; q != NULL; q = q->prox){
        printf("Grupo ID: %d\tPosicao: %d\tQtd pessoas: %d\n", q->identificacao, posicao, q->quantidadeMembros);
        posicao++;
        totalNaFila += q->quantidadeMembros;
    }
    printf ("Existem %d pessoas na fila.\n", totalNaFila);
}

Fila *sairDaFila(Fila* f, Grupo *listaGrupos)
{   
    int idLocal;
    Grupo* p = f->ini;
    Grupo *ant = NULL;

    if(f->ini == NULL)
    {
        printf("\nFila de espera vazia\n");
        return f;
    }
    filaImprime(f);

    printf ("Digite o id do grupo que deseja sair da fila: \n");
    scanf ("%d", &idLocal); 

    while(p != NULL && p->identificacao != idLocal){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        printf("Id nao encontrado.\n");
        return f;
    }

    if(ant == NULL){
        f->ini = f->ini->prox;
        Grupo *anteriorFini = listaGrupos;
        while (anteriorFini->prox != NULL && anteriorFini->prox != p)
        {
            anteriorFini = anteriorFini->prox;
        }
        anteriorFini->prox = NULL;
    }else{
        ant->prox = p->prox;        
    }

    if(f->ini == NULL)
    {
        f->fim = NULL;
        Grupo *ultimoGrupo = listaGrupos;
        while (ultimoGrupo->prox != NULL)
        {
            ultimoGrupo = ultimoGrupo->prox;
        }
        ultimoGrupo->prox = NULL;
    }

    printf ("O grupo com id %d saiu da fila.\n", p->identificacao);
    free(p);
    
    return f;
}

Fila *puxaDaFila (Fila *filaEspera, Grupo* p, Pilha *pilha, Mesa *vetor, int linhas, int colunas)
{
    Fila *f = filaEspera;
    int quantidadeSaindo = p->mesaAtribuida->quantidadeSentada;

    if(f->ini != NULL)  /* fila nao esta vazia */
    {
        int quantidadeEntrando = f->ini->quantidadeMembros;

        colocaPratosFaltam(pilha, quantidadeSaindo);
        p->mesaAtribuida->ocupada = LIV;

        f->ini->mesaAtribuida = atribuiMesa(vetor, linhas, colunas, quantidadeEntrando, pilha);

        f->ini = f->ini->prox;
        if(f->ini == NULL)
        {
            f->fim = NULL;
        }
    
    }
    else    /* fila esta vazia */
    {
        colocaPratosFaltam(pilha, quantidadeSaindo);
        p->mesaAtribuida->quantidadeSentada = 0;
        p->mesaAtribuida->ocupada = LIV;
    }
    
    return f;
}

Grupo *liberarMesa(Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
{   
    Grupo *p = inicioLista;
    Grupo *ant = NULL;
    int numero;

    if(p == NULL)
    {
        printf("Nao existem mesas ocupadas\n");
        return inicioLista;
    }

    imprimeMesasTodas(vetor, linhas, colunas);

    printf ("Digite o numero da mesa: \n");
    scanf ("%d", &numero);
    
    while(p != NULL && p->mesaAtribuida != NULL && p->mesaAtribuida->numero != numero)
    {
        ant = p;
        p = p->prox;
    }

    if(p == NULL || p->mesaAtribuida == NULL)
    {
        printf("Essa mesa nao esta ocupada\n");
        return inicioLista;
    }
    
    if(ant == NULL)
    {
        inicioLista = p->prox;
    }
    else
    {
        ant->prox = p->prox;        
    }

    filaEspera = puxaDaFila (filaEspera, p, pilha, vetor, linhas, colunas);
    
    free(p);
    
    return inicioLista;
}

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
{
    /* alocando o grupo */
    Grupo *novo = (Grupo*)malloc(sizeof(Grupo));
    if (novo == NULL)
    {
        printf ("Falha de alocacao. O programa sera encerrado.\n");
        exit (1);
    }
    
    /* setando as informacoes do novo grupo */
    if (quantidadeMembros > 4)
    {
        novo->quantidadeMembros = 4;
    }
    else
    {
        novo->quantidadeMembros = quantidadeMembros;
    }
    novo->prox = NULL;
    
    /* incluindo na lista */ 
    if (inicioLista == NULL)
    {
        inicioLista = novo;
        novo->identificacao = 0;
    }
    else
    {   
        Grupo *p = inicioLista;
        while (p->prox != NULL)
        {
            p = p->prox;
        }
        novo->identificacao = p->identificacao + 1;
        p->prox = novo;
        
    }  

    novo->mesaAtribuida = atribuiMesa (vetor, linhas, colunas, novo->quantidadeMembros, pilha);
    
    if (novo->mesaAtribuida == NULL)
    {
        /* aqui adicionar o grupo na fila de espera */
        filaInsere(filaEspera, novo);
    }

    return inicioLista;
}

Grupo *addGrupo (Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
{
    int quantidadeMembros;
    printf ("Digite a quantidade de membros do grupo: ");
    scanf ("%d", &quantidadeMembros);

    while (quantidadeMembros > 4)
    {
        inicioLista = alocaNovoGrupo (inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera, pilha);
        quantidadeMembros -= 4;
    }
    
    inicioLista = alocaNovoGrupo (inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera, pilha);

    return inicioLista;

}

void imprimeGrupos (Grupo *inicioLista)
{
    Grupo *p;
    printf("\nImprimindo grupos...\n");
    for (p = inicioLista; p != NULL; p = p->prox)
    {
        printf ("Quantidade de membros: %d\t", p->quantidadeMembros);
        printf ("ID: %d\n", p->identificacao);
    }
}