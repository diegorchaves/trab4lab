#include <stdio.h>
#include <stdlib.h>

#define LIV 0
#define OCP 1

/* definir os tipos */

typedef struct mesa
{
    int numero;
    int ocupada;
    int quantidadeSentada;
    int numeroComanda;
} Mesa;

typedef struct grupo
{
    int quantidadeMembros;
    int identificacao;
    struct grupo *prox;
    Mesa *mesaAtribuida;
} Grupo;

/* funcao que aloca as mesas e retorna o endereco para o vetor de mesas */
Mesa *alocaMesas (int linhas, int colunas)
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

Mesa *atribuiMesa (Mesa *vetor, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (vetor[i * colunas + j].ocupada == LIV)
            {
                printf ("Mesa %d designada.\n", vetor [i * colunas + j].numero);
                vetor[i * colunas + j].ocupada = OCP;
                return &vetor[i * colunas + j];
            }
        }
    }
    printf ("Nao existem mesas disponiveis, o(s) grupo(s) ficara(o) na fila de espera.\n");
    return NULL;
}

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas)
{
    int idGrupo;

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

    /* incluindo na fila */
    if (inicioLista == NULL)
    {
        inicioLista = novo;
        idGrupo = 0;
    }
    else
    {
        Grupo *p = inicioLista;
        while (p->prox != NULL)
        {
            p = p->prox;
        }
        idGrupo = p->identificacao + 1;
        p->prox = novo;
    }

    novo->identificacao = idGrupo;
    novo->mesaAtribuida = atribuiMesa (vetor, linhas, colunas);
    if (novo->mesaAtribuida == NULL)
    {
        /* aqui adicionar o grupo na fila de espera */
    }

    return inicioLista;
}

void addGrupo (Grupo **inicioLista, Mesa *vetor, int linhas, int colunas)
{
    int quantidadeMembros;
    printf ("Digite a quantidade de membros do grupo: ");
    scanf ("%d", &quantidadeMembros);

    while (quantidadeMembros > 4)
    {
        *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas);
        quantidadeMembros -= 4;
    }

    *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas);

}

void imprimeGrupos (Grupo *inicioLista)
{
    Grupo *p;
    for (p = inicioLista; p != NULL; p = p->prox)
    {
        printf ("Quantidade de membros: %d\t", p->quantidadeMembros);
        printf ("ID: %d\n", p->identificacao);
    }
}

void imprimeMesasLivres (Mesa *vetor, int linhas, int colunas)
{
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

int main ()
{
    /* vetor de mesas */
    Mesa *vetorMesas = NULL;

    /* lista que guarda os grupos */
    Grupo *listaGrupos = NULL;

    /* fila de espera */
    Grupo *filaEspera = NULL;

    /* perguntar ao usuario quantas linhas e colunas de mesas existem */
    int linhas, colunas;
    printf ("Informe o numero de linhas: ");
    scanf ("%d", &linhas);
    printf ("Informe o numero de colunas: ");
    scanf ("%d", &colunas);

    /* alocar dinamicamente as mesas */
    vetorMesas = alocaMesas (linhas, colunas);

    /* incluir um novo grupo */
    addGrupo (&listaGrupos, vetorMesas, linhas, colunas);

    imprimeGrupos (listaGrupos);

    imprimeMesasLivres (vetorMesas, linhas, colunas);

}