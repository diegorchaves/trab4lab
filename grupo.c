#include <stdlib.h>
#include <stdio.h>
#include "mesa.h"
#include "grupo.h"
#define OCP 0
#define LIV 1

Grupo* criaGrupo(int qtdPessoas)
{
    Grupo* novo = (Grupo*)malloc(sizeof(Grupo));

    novo->qtdPessoasGrupo = qtdPessoas;
    novo->idGrupo = 0;
    novo->prox = NULL;

    return novo;
}

Grupo *criaSubGrupo(Grupo *listaGrupos, int qtdPessoas)
{
    Grupo *novo = (Grupo*)malloc(sizeof(Grupo));
    

    if(qtdPessoas <= 4)
    {   
        if(listaGrupos == NULL)
        {
            novo->qtdPessoasGrupo = qtdPessoas;
            novo->idGrupo = 0;
            novo->prox = NULL;
            
            return novo;
        }

        Grupo *p;
        for(p = listaGrupos; p->prox != NULL; p = p->prox)
        {}

        novo->qtdPessoasGrupo = qtdPessoas;
        novo->idGrupo = 0;
        novo->prox = NULL;
        p->prox = novo;

        return listaGrupos;
        
    }else{
        novo->qtdPessoasGrupo = 4;
        novo->idGrupo = 0;
        novo->prox = listaGrupos;

        novo = criaSubGrupo(novo, qtdPessoas - 4);
    }

    return novo;
}

void imprimeListaSubgrupos(Grupo *listaGrupos)
{
    Grupo *p;
    int i = 1;

    for(p = listaGrupos; p != NULL; p = p->prox){
        printf("Grupo: %d, qtdPessoas: %d \n", i, p->qtdPessoasGrupo);
        i++;
    }
}

int perguntaQtdPessoas()
{   
    int qtdPessoas;
    printf ("Informe a quantidade de pessoas do grupo: ");
    scanf ("%d", &qtdPessoas);

    return qtdPessoas;
}

void enfileirarSubgrupos(Grupo *p, Grupo* fila)
{
    Grupo *temp = fila;
    while (temp->prox != NULL)
    {
        temp = temp->prox;
    }
    temp->prox = p;
}

void preencheMesas(Mesa *vetorMesas, int qtdLinhas, int qtdColunas, Grupo *listaSubGrupos, Grupo *fila)
{   
    Grupo *p = listaSubGrupos;
    int i = 0;
    while(p != NULL)
    {
        if(i > qtdLinhas*qtdColunas){
            break;                  // tratar os subgrupos que sobraram para por na fila
        }

        if(vetorMesas[i].livre == LIV){
            vetorMesas[i].livre = OCP;
            p = p->prox;
        }
        
        i++;
    }

    enfileirarSubgrupos(p, fila);
}

void chegaGrupo(Mesa *vetorMesas, Grupo *fila, int qtdLinhas, int qtdColunas)
{
    int qtdPessoas = perguntaQtdPessoas();

    Grupo* grupo;   
    grupo = criaGrupo(qtdPessoas);

    Grupo *listaSubGrupos = NULL;
    listaSubGrupos = criaSubGrupo(listaSubGrupos, grupo->qtdPessoasGrupo);

    imprimeListaSubgrupos(listaSubGrupos);

    preencheMesas(vetorMesas, qtdLinhas, qtdColunas, listaSubGrupos, fila);
}

