#include <stdio.h>
#include <stdlib.h>
#define OCP 0
#define LIV 1

typedef struct mesa
{
    int numeroMesa;
    int livre;
    int qtdPessoasSentadas;
    int numeroComanda;
} Mesa;

typedef struct grupo
{
    int qtdPessoasGrupo;
    int idGrupo;
    struct grupo *prox;
} Grupo;


//  é possível usar uma lista de grupos, ao inserir ordenar por idGrupo.
//  ao chegar um grupo, se tiver mais que 4 pessoas, criar um segundo nó com as pessoas restantes.

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

int perguntaLinhasColunas(int *qtdLinhas, int *qtdColunas)
{

    printf ("Informe linhas: ");
    scanf ("%d", qtdLinhas);
    printf ("Informe colunas: ");
    scanf ("%d", qtdColunas);

    return *qtdLinhas * *qtdColunas;
}   

Grupo* criaGrupo(int qtdPessoas)
{
    Grupo* novo = (Grupo*)malloc(sizeof(Grupo));

    novo->qtdPessoasGrupo = qtdPessoas;
    novo->idGrupo = 0;
    novo->prox = NULL;
}

Grupo *criaSubGrupo(Grupo *listaGrupos, int qtdPessoas)
{
    Grupo *novo = (Grupo*)malloc(sizeof(Grupo));

    if(qtdPessoas <= 4)
    {
        novo->qtdPessoasGrupo = qtdPessoas;
        novo->idGrupo = 0;
        novo->prox = listaGrupos;
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

void imprimeMesasOcupadas(Mesa *vetorMesas, int qtdLinhas, int qtdColunas)
{
    for (int i = 0; i < qtdLinhas; i++)
    {
        {
            for (int j = 0; j < qtdColunas; j++)
            {   
                if(vetorMesas[i*qtdColunas+j].livre = LIV){
                    int numeroMesa = i*qtdColunas+j+1;
                    printf("Mesa %d livre\n", numeroMesa);
                }
            }
        }
    }
}

int main ()
{
    int qtdMesas, qtdLinhas, qtdColunas;
    Mesa *vetorMesas;
    
    qtdMesas = perguntaLinhasColunas(&qtdLinhas, &qtdColunas);

    vetorMesas = alocaVetor (qtdMesas);

    setaMesasIniciais (vetorMesas, qtdLinhas, qtdColunas);
    imprimeMesasOcupadas(vetorMesas, qtdLinhas, qtdColunas);
    
    int qtdPessoas = perguntaQtdPessoas();
    Grupo* grupo;   
    grupo = criaGrupo(qtdPessoas);

    Grupo *listaSubGrupos = NULL;
    listaSubGrupos = criaSubGrupo(listaSubGrupos, grupo->qtdPessoasGrupo);

    imprimeListaSubgrupos(listaSubGrupos);
    
}
