typedef struct prato
{
    struct prato *prox;
} Prato;

typedef struct pilha
{
    Prato *prim;
} Pilha;


void push (Pilha *pilha);

void pop (Pilha *pilha);

void reporPratos (Pilha *pilha);

Pilha* pratoInicializa(Pilha *pilhaPratos, int linhas, int colunas);

void contaPratos (Pilha *pil);

void retiraPratosExcedentes (Pilha *pilha, int quantidadeMembros);

void colocaPratosFaltam (Pilha *pilha, int quantidadeMembros);

Pilha *initPilha ();