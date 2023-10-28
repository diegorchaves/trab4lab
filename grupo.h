typedef struct grupo
{
    int quantidadeMembros;
    int identificacao;
    struct grupo *prox;
    Mesa *mesaAtribuida;
} Grupo;


typedef struct fila
{
    Grupo *ini;
    Grupo *fim;
} Fila;

Fila *filaInicializa();

void filaInsere (Fila* filaEspera, Grupo *novo);

void filaImprime(Fila* f);

Fila *sairDaFila(Fila* f, Grupo *listaGrupos);

Fila *puxaDaFila (Fila *filaEspera, Grupo* p, Pilha *pilha, Mesa *vetor, int linhas, int colunas);

Grupo *liberarMesa(Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha);

Grupo *alocaNovoGrupo (Grupo *inicioLista, int quantidadeMembros, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha);

Grupo *addGrupo (Grupo *inicioLista, Mesa *vetor, int linhas, int colunas, Fila *filaEspera, Pilha *pilha);

void imprimeGrupos (Grupo *inicioLista);