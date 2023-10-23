typedef struct grupo
{
    int qtdPessoasGrupo;
    int idGrupo;
    struct grupo *prox;
} Grupo;


Grupo* criaGrupo(int qtdPessoas);

Grupo *criaSubGrupo(Grupo *listaGrupos, int qtdPessoas);

void imprimeListaSubgrupos(Grupo *listaGrupos);

int perguntaQtdPessoas();

void enfileirarSubgrupos(Grupo *p, Grupo* fila);

void chegaGrupo(Mesa *vetorMesas, Grupo *fila, int qtdLinhas, int qtdColunas);

void preencheMesas(Mesa *vetorMesas, int qtdLinhas, int qtdColunas, Grupo *listaSubGrupos, Grupo *fila);