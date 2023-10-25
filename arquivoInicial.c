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
    struct grupo *ini;
    struct grupo *fim;
} Fila;

typedef struct pilha
{
    struct prato *prim;
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

Pilha* pratoInicializa(Pilha* pilhaPrato, int linhas, int colunas)
{
    int quantidadePratos = linhas * colunas * 4;

    for(int i = 0; i < quantidadePratos; i++){
        push(pilhaPrato);
    }

    return pilhaPrato;
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

Pilha* pilhaInicializa()
{
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->prim = NULL;

    return p;
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

void ColocaPratosFaltam (Pilha *pilha, int quantidadeMembros)
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

    if(f->ini == NULL){
        printf("\nFila de Espera vazia\n");
        return;
    }

    printf("\nImprimindo Fila de Espera...\n");
    for(q = f->ini; q != NULL; q = q->prox){
        printf("Grupo ID: %d \n", q->identificacao);
    }
}

void sairDaFila(Fila* f)
{   
    int idLocal;
    Grupo* p = f->ini;
    Grupo *ant = NULL;

    if(f == NULL){
        printf("\nFila de Espera vazia\n");
        return;
    }
    filaImprime(f);

    printf ("Digite o Id do grupo que deseja sair da fila: \n");
    scanf (" %d", &idLocal); 

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
    free(p);
}

Grupo *liberarMesa(Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila **filaEspera, Pilha *pilha)
{   
    Grupo *p = inicioLista;
    Grupo *ant = NULL;
    int comanda = 0;

    if(inicioLista == NULL)
    {
        printf("Nao existem mesas ocupadas\n");
        return inicioLista;
    }

    printf ("Digite o numero da comanda: \n");
    scanf (" %d", &comanda);
    
    while(p != NULL && p->mesaAtribuida != NULL && p->mesaAtribuida->numeroComanda != comanda){
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
    }else{
        ant->prox = p->prox;        
    }

    
    // SE HOUVER ALGUEM NA FILA ATRIBUI MESA
    Fila *f = *filaEspera;
    int quantidadeSaindo = p->mesaAtribuida->quantidadeSentada;

    if(f->ini != NULL){
        int quantidadeEntrando = f->ini->quantidadeMembros;

        ColocaPratosFaltam(pilha, quantidadeSaindo);
        p->mesaAtribuida->ocupada = LIV;

        f->ini->mesaAtribuida = atribuiMesa(vetor, linhas, colunas, quantidadeEntrando, pilha);

        f->ini = f->ini->prox;
    
    }else{
        ColocaPratosFaltam(pilha, quantidadeSaindo);
        p->mesaAtribuida->ocupada = LIV;
    }
    free(p);
    return inicioLista;

}

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas, Fila **filaEspera, Pilha *pilha)
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
    novo->mesaAtribuida = atribuiMesa (vetor, linhas, colunas, novo->quantidadeMembros, pilha);
    if (novo->mesaAtribuida == NULL)
    {
        /* aqui adicionar o grupo na fila de espera */
        filaInsere(*filaEspera, novo);
    }

    return inicioLista;
}

void addGrupo (Grupo **inicioLista, Mesa *vetor, int linhas, int colunas, Fila **filaEspera, Pilha *pilha)
{
    int quantidadeMembros;
    printf ("Digite a quantidade de membros do grupo: ");
    scanf ("%d", &quantidadeMembros);

    while (quantidadeMembros > 4)
    {
        *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera, pilha);
        quantidadeMembros -= 4;
    }

    *inicioLista = alocaNovoGrupo (*inicioLista, quantidadeMembros, vetor, linhas, colunas, filaEspera, pilha);

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

    /* lista que guarda pratos */
    Prato *listaPratos = NULL;

    /* fila de espera */
    Fila *filaEspera = filaInicializa();

    /* pilha de pratos*/
    Pilha *pilhaPrato = pilhaInicializa();

    /* perguntar ao usuario quantas linhas e colunas de mesas existem */
    int linhas, colunas;
    printf ("Informe o numero de linhas: ");
    scanf ("%d", &linhas);
    printf ("Informe o numero de colunas: ");
    scanf ("%d", &colunas);

    /* preencher lista de pratos*/
    pilhaPrato = pratoInicializa(pilhaPrato, linhas, colunas);

    contaPratos(pilhaPrato);

    /* alocar dinamicamente as mesas */
    vetorMesas = alocaMesas (linhas, colunas, pilhaPrato);

    /* incluir um novo grupo */
    addGrupo (&listaGrupos, vetorMesas, linhas, colunas, &filaEspera, pilhaPrato);

    imprimeGrupos (listaGrupos);

    imprimeMesasLivres (vetorMesas, linhas, colunas);

    filaImprime(filaEspera);

    listaGrupos = liberarMesa(listaGrupos, vetorMesas, linhas, colunas, &filaEspera, pilhaPrato);

    sairDaFila(filaEspera);

}
