#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int quant;
    char num[30];
} conteudoNo;

typedef struct no {
    conteudoNo dado;
    struct no *ant;
} No;

typedef struct pilha {
    No *inicio;
    No *fim;
} Pilha;

void iniciaPilha(Pilha *p) {
    p->inicio = NULL;
    p->fim = NULL;
}

int fila_vazia (Pilha *p){
    return p->fim == NULL && p->inicio == NULL;
}

void insereNo(Pilha *p, conteudoNo n) {
    No *aux = (No*) malloc(sizeof(No));
    aux->dado = n;
    aux->ant = NULL;

    if (p->fim == NULL) {
        p->inicio = aux;
    } else {
        p->fim->ant = aux;
    }
    
    p->fim = aux;
}

void remover(Pilha *p, char* r_id) {
    No *atual = p->inicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dado.num, r_id) == 0) {
            if (anterior == NULL) {
                p->inicio = atual->ant;
            } else {
                anterior->ant = atual->ant;
            }
            if (atual == p->fim) {
                p->fim = anterior;
            }

            free(atual);
            printf("Nó com ITEM %s removido com sucesso.\n", r_id);
            return;
        }

        anterior = atual;
        atual = atual->ant;
    }

    printf("Nó com ITEM %s não encontrado na fila.\n", r_id);
}

void mostrar(Pilha *p, conteudoNo n) {
    No *aux = p->inicio;
    
    if (aux == NULL) {
        printf("A fila esta vazia.\n");
    }
    else {
        printf("conteudo da fila:\n");
        while (aux != NULL) {
            printf("ITEM:%s \n", aux->dado.num);
            printf("quant: %d \n\n", aux->dado.quant);
            aux = aux->ant;
        }
    }
}
int main() {
    Pilha p;
    conteudoNo n;
    iniciaPilha(&p);

    int comando, valor,j=10;
    char r_id[15];
    do {
        printf("\n=== Menu ===\n");
        printf("1. Empilha\n");
        printf("2. Remove\n");
        printf("3. Mostrar\n");
        printf("4. Sair\n");
        scanf("%d", &comando);

        switch (comando) {
            case 1:
                printf("Digite o ITEM a ser inserido: ");
                scanf("%s", &n.num);
                printf("Digite a QUANTIDADE: ");
                scanf("%i", &n.quant);
                insereNo(&p, n);
                break;
            case 2:
                if (fila_vazia(&p)) {
                  printf("A fila está vazia.\n");
                  break;
                }
                printf("qual item para remover:");
                scanf("%s", &r_id);
                remover(&p,r_id);
                break;
            case 3:
                mostrar(&p,n);
                break;
            case 4:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Comando inválido\n");
                break;
        }
    } while (comando != 4);

    return 0;
}
