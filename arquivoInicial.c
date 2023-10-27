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

typedef struct prato
{
    struct prato *prox;
} Prato;

typedef struct fila
{
    Grupo *ini;
    Grupo *fim;
} Fila;

typedef struct pilha
{
    Prato *prim;
} Pilha;

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

/* funcao que aloca as mesas e retorna o endereco para o vetor de mesas */
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

Fila *filaInicializa()
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;

    return f;
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
    int posicao = 1, totalNaFila = 0;

    if(f->ini == NULL){
        printf("\nFila de Espera vazia\n");
        return;
    }

    printf("\nImprimindo Fila de Espera...\n");
    for(q = f->ini; q != NULL; q = q->prox){
        printf("Grupo ID: %d\tPosicao: %d\tQtd pessoas: %d\n", q->identificacao, posicao, q->quantidadeMembros);
        posicao++;
        totalNaFila += q->quantidadeMembros;
    }
    printf ("Existem %d pessoas na fila.\n", totalNaFila);
}

void sairDaFila(Fila* f)
{   
    int idLocal;
    Grupo* p = f->ini;
    Grupo *ant = NULL;

    if(f == NULL)
    {
        printf("\nFila de Espera vazia\n");
        return;
    }
    filaImprime(f);

    printf ("Digite o Id do grupo que deseja sair da fila: \n");
    scanf ("%d", &idLocal); 

    while(p != NULL && p->identificacao != idLocal){
        ant = p;
        p = p->prox;
    }

    if(p == NULL){
        printf("Id nao encontrado.\n");
        return;
    }

    if(ant == NULL){
        f->ini = f->ini->prox;
    }else{
        ant->prox = p->prox;        
    }
    printf ("O grupo com Id %d saiu da fila.\n", p->identificacao);
    free(p);
}

void puxaDaFila (Fila *filaEspera, Grupo* p, Pilha *pilha, Mesa *vetor, int linhas, int colunas)
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
    
    }
    else    /* fila esta vazia */
    {
        colocaPratosFaltam(pilha, quantidadeSaindo);
        p->mesaAtribuida->ocupada = LIV;
    }
}

Grupo *liberarMesa(Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
{   
    Grupo *p = inicioLista;
    Grupo *ant = NULL;
    int comanda;

    if(p == NULL)
    {
        printf("Nao existem mesas ocupadas\n");
        return inicioLista;
    }

    printf ("Digite o numero da comanda: \n");
    scanf ("%d", &comanda);
    
    while(p != NULL && p->mesaAtribuida != NULL && p->mesaAtribuida->numeroComanda != comanda)
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

    puxaDaFila (filaEspera, p, pilha, vetor, linhas, colunas);
    
    free(p);
    
    return inicioLista;
}

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
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

void addGrupo (Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha)
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
                addGrupo (listaGrupos, vetorMesas, linhas, colunas, filaEspera, *pilhaPratos);
                break;
            case 2:
                listaGrupos = liberarMesa(listaGrupos, vetorMesas, linhas, colunas, filaEspera, *pilhaPratos);
                break;
            case 3:
                sairDaFila(filaEspera);
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

    menu (listaGrupos, vetorMesas, linhas, colunas, filaEspera, &pilhaPratos);

    /* contaPratos(pilhaPratos);
    addGrupo (&listaGrupos, vetorMesas, linhas, colunas, &filaEspera, pilhaPratos);
    imprimeGrupos (listaGrupos);
    imprimeMesasLivres (vetorMesas, linhas, colunas);
    filaImprime(filaEspera);
    listaGrupos = liberarMesa(listaGrupos, vetorMesas, linhas, colunas, &filaEspera, pilhaPratos);
    sairDaFila(filaEspera); */

}
