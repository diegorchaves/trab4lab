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

typedef struct fila
{
    struct grupo *ini;
    struct grupo *fim;
} Fila;

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

Fila *filaInicializa()
{
     Fila* p;

     p->ini = NULL;
     p->fim = NULL;

     return p;
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

void filaInsere (Fila* filaEspera, Grupo *novo)
{
    
    if (filaEspera->fim != NULL){
        filaEspera->fim->prox = novo;
    } else{
        filaEspera->ini = novo;
    }
    filaEspera->fim = novo; 

}

void filaImprime(Fila* f){
    Grupo* q;

    if(f->ini == NULL){
        printf("\nFila de Espera vazia\n");
        return;
    }

    for(q = f->ini; q != NULL; q = q->prox){
        printf("\nImprimindo Fila de Espera...\n");
        printf("Grupo ID: %d \n", q->identificacao);
    }
}

Grupo *liberarMesa(Grupo *inicioLista)
{   
    Grupo *p = inicioLista;
    Grupo *ant = inicioLista;
    int comanda = 0;

    if(inicioLista == NULL)
    {
        printf("Nao existem mesas ocupadas\n");
        return inicioLista;
    }

    printf ("Digite o numero da comanda: \n");
    scanf (" %d", &comanda);
    
    while(p != NULL && p->mesaAtribuida->numeroComanda != comanda){
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
    {
        printf("Essa mesa nao esta ocupada\n");     
    }else if(ant == inicioLista)
    {
        p->mesaAtribuida->ocupada = LIV;
        inicioLista = p->prox;
        free(p);
    }else{
        p->mesaAtribuida->ocupada = LIV;
        ant->prox = p->prox;        
        free(p);
    }

    // AQUI PRECISA AJEITAR QUEM ESTA FILA
    return inicioLista;

}

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas, Fila **filaEspera)
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
        filaInsere(*filaEspera, novo);
    }

    return inicioLista;
}

void addGrupo (Grupo **inicioLista, Mesa *vetor, int linhas, int colunas, Fila **filaEspera)
{
    int quantidadeMembros;
    printf ("Digite a quantidade de membros do grupo: ");
    scanf ("%d", &quantidadeMembros);

    while (quantidadeMembros > 4)
    {
        *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera);
        quantidadeMembros -= 4;
    }

    *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera);

}

void imprimeGrupos (Grupo *inicioLista)
{
    Grupo *p;
    printf("\nImprimindo Grupos...\n");
    for (p = inicioLista; p != NULL; p = p->prox)
    {
        printf ("Quantidade de membros: %d\t", p->quantidadeMembros);
        printf ("ID: %d\n", p->identificacao);
    }
}

void imprimeMesasLivres (Mesa *vetor, int linhas, int colunas)
{   
    printf("\nImprimindo Mesas Livres...\n");
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




int main ()
{
    /* vetor de mesas */
    Mesa *vetorMesas = NULL;

    /* lista que guarda os grupos */
    Grupo *listaGrupos = NULL;

    /* fila de espera */
    Fila *filaEspera = filaInicializa();

    /* perguntar ao usuario quantas linhas e colunas de mesas existem */
    int linhas, colunas;
    printf ("Informe o numero de linhas: ");
    scanf ("%d", &linhas);
    printf ("Informe o numero de colunas: ");
    scanf ("%d", &colunas);

    /* alocar dinamicamente as mesas */
    vetorMesas = alocaMesas (linhas, colunas);

    /* incluir um novo grupo */
    addGrupo (&listaGrupos, vetorMesas, linhas, colunas, &filaEspera);

    imprimeGrupos (listaGrupos);

    imprimeMesasLivres (vetorMesas, linhas, colunas);

    filaImprime(filaEspera);

    listaGrupos = liberarMesa(listaGrupos);

    imprimeGrupos (listaGrupos);

    imprimeMesasLivres (vetorMesas, linhas, colunas);
}
