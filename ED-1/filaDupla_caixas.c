#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    int num;
} conteudoNo;

typedef struct no {
    conteudoNo dado;
    struct no* prox;
    struct no *ant;
} No;

typedef struct fila {
    No *inicio;
    No *fim;
} Fila;

void iniciafila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int fila_vazia (Fila *f){
    return f->fim == NULL && f->inicio == NULL;
}

void insereNo(Fila *f, conteudoNo n) {
    No *aux = (No*) malloc(sizeof(No));
    aux->dado = n;
    aux->ant = NULL;

    if (f->inicio == NULL) {
        f->inicio = aux;
        f->fim = aux;
    } else {
         aux->ant = f->fim;
        f->fim->prox = aux;
        f->fim = aux;
      }    
}

void remover(Fila* f, int id_remo) {
    No *atual = f->inicio;

    while (atual != NULL) {
        if (atual->dado.id == id_remo) {
            if (atual == f->inicio) {
                f->inicio = atual->prox;
                if (f->inicio == NULL) {  // Caso seja o único nó da fila
                    f->fim = NULL;
                } else {
                    f->inicio->ant = NULL;
                }
            } else if (atual == f->fim) {  // Verifica se é o último nó da fila
                f->fim = atual->ant;
                f->fim->prox = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }

            free(atual);
            printf("Nó com ID %d removido com sucesso.\n", id_remo);
            return;
        }

        atual = atual->prox;
    }

    printf("Nó com ID %d não encontrado na fila.\n", id_remo);
}



void mostrar(Fila *f, conteudoNo n) {
    No *aux = f->inicio;
    
    if (fila_vazia(f)) {
        printf("A fila esta vazia.\n");
    } else {
        printf("Conteudo da fila:\n");
        while (aux != NULL) {
            printf("ID: %d | Numero: %d\n", aux->dado.id, aux->dado.num);
            aux = aux->prox;
        }
    }
}

int main() {
    Fila f;
    conteudoNo n;
    iniciafila(&f);

    int comando,r_id,j=10;

    do {
        printf("\n=== Menu ===\n");
        printf("1. emfileira\n");
        printf("2. Remove\n");
        printf("3. Mostrar\n");
        printf("4. Sair\n");
        scanf("%d", &comando);

        switch (comando) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &n.num);
                for(int i = j; i <= 50; i++){
                    n.id = i;
                    j++;
                    break;
                }
                insereNo(&f, n);
                break;
            case 2:
                if (fila_vazia(&f)) {
                  printf("A fila está vazia.\n");
                  break;
                }
                printf("qual id para remover:");
                scanf("%d", &r_id);
                remover(&f,r_id);
                break;
            case 3:
                mostrar(&f,n);
                break;
            case 4:
                printf("Encerrando o programa...\n");
                break;

        }
    } while (comando != 4);

    return 0;
}
