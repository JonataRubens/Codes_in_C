#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    int num;
} conteudoNo;

typedef struct no {
    conteudoNo dado;
    struct no *ant;
} No;

typedef struct fila {
    No *inicio;
    No *fim;
  }fila;

void iniciaFila(fila *p) {
    p->inicio = NULL;
    p->fim = NULL;
}

int fila_vazia (fila *p){
    return p->fim == NULL && p->inicio == NULL;
}

void insereNo(fila *p, conteudoNo n) {
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

void remover(fila *p, int r_id) {
    if (fila_vazia(p)) {
        printf("A fila está vazia.\n");
        return;
    }

    No *atual = p->inicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (atual->dado.id == r_id) {
            if (anterior == NULL) {
                // O nó a ser removido é o primeiro da fila
                p->inicio = atual->ant;
            } else {
                anterior->ant = atual->ant;
            }

            // Verifica se o nó a ser removido é o último da fila
            if (atual == p->fim) {
                p->fim = anterior;
            }

            free(atual);
            printf("Nó com ID %d removido com sucesso.\n", r_id);
            return;
        }

        anterior = atual;
        atual = atual->ant;
    }

    printf("Nó com ID %d não encontrado na fila.\n", r_id);
}


void mostrar(fila *p, conteudoNo n) {
    No *aux = p->inicio;
    
    if (aux == NULL) {
        printf("A fila esta vazia.\n");
    }
    else {
        printf("conteudo da fila:\n");
        while (aux != NULL) {
            printf("%d ", aux->dado.id);
            aux = aux->ant;
        }
    }
}
int main() {
    fila p;
    conteudoNo n;
    iniciaFila(&p);

    int comando, valor,r_id,j=1,i;

    do {
        printf("\n=== Menu ===\n");
        printf("1. Empilha\n");
        printf("2. Remove\n");
        printf("3. Mostrar\n");
        printf("4. Sair\n");
        scanf("%d", &comando);

        switch (comando) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &n.id);
                for(int i = j; i <= 50; i++){
                    conteudoNo.id = i;
                    j++;
                    break;
                }
                insereNo(&p, n);
                break;
            case 2:
                printf("qual id para remover:");
                scanf("%d", &r_id);
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
