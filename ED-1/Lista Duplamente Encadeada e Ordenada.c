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
} lista;

int lista_vazia (lista *L){
    return L->fim == NULL && L->inicio == NULL;
}

void insereNo(lista *L, conteudoNo n) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = n;
    novo->prox = NULL;
    novo->ant = NULL;

    if (L->inicio == NULL) {
        L->inicio = novo;
        L->fim = novo;
    } else {
        No *atual = L->inicio;
        No *anterior = NULL;

        while (atual != NULL && atual->dado.num < novo->dado.num) {
            anterior = atual;
            atual = atual->prox;
        }

        if (anterior == NULL) {
            // Inserção no início da lista
            novo->prox = L->inicio;
            L->inicio->ant = novo;
            L->inicio = novo;
        } else if (atual == NULL) {
            // Inserção no final da lista
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        } else {
            // Inserção no meio da lista
            novo->prox = atual;
            novo->ant = anterior;
            anterior->prox = novo;
            atual->ant = novo;
        }
    }
}



//void inserir_posicao(lista *L, conteudoNo n, int posicao) {
//}

void remover_id(lista* L, int id_remo) {
    No *atual = L->inicio;

    while (atual != NULL) {
        if (atual->dado.id == id_remo) {
            if (atual == L->inicio) {
                L->inicio = atual->prox;
                if (L->inicio == NULL) {  
                    L->fim = NULL;
                } else {
                    L->inicio->ant = NULL;
                }
            } else if (atual == L->fim) {  
                L->fim = atual->ant;
                L->fim->prox = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }

            free(atual);
            printf("Nó com ID %d removido.\n", id_remo);
            return;
        }

        atual = atual->prox;
    }

    printf("Nó com ID %d não encontrado.\n", id_remo);
}

void remover_posicao(lista* L, int posicao) {
    No *atual = L->inicio;
    int contador = 0;

    while (atual != NULL) {
        if (contador == posicao) {
            if (atual == L->inicio) {
                L->inicio = atual->prox;
                if (L->inicio == NULL) {  
                    L->fim = NULL;
                } else {
                    L->inicio->ant = NULL;
                }
            } else if (atual == L->fim) {  
                L->fim = atual->ant;
                L->fim->prox = NULL;
            } else {
                atual->ant->prox = atual->prox;
                atual->prox->ant = atual->ant;
            }

            free(atual);
            printf("Nó na posição %d removido.\n", posicao);
            return;
        }

        atual = atual->prox;
        contador++;
    }

    printf("Posição %d não encontrada.\n", posicao);
}

void mostrar(lista *L, conteudoNo n) {
    No *aux = L->inicio;
    int i=0;
    if (lista_vazia(L)) {
        printf("A fila esta vazia.\n");
    } else {
        printf("Conteudo da fila:\n");
        while (aux != NULL) {
            printf("posicao: %d |-> ID: %d |-> Numero: %d\n",i, aux->dado.id, aux->dado.num);
            aux = aux->prox;
            i++;
        }
    }
}

int main() {
    lista L;
    conteudoNo n;
    L.inicio = NULL;
    L.fim = NULL;

    int comando,r_id,j=10,r_posicao,position;

    do {
        printf("\n=== Menu ===\n");
        printf("1. emfileira\n");
        printf("2. Remove por ID\n");
        printf("3. Remove por posicao\n");
        printf("4. Mostrar\n");
        printf("0. Sair\n");
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
                insereNo(&L, n);
                break;
            case 2:
                if (lista_vazia(&L)) {
                  printf("A fila está vazia.\n");
                  break;
                }
                printf("qual id para remover:");
                scanf("%d", &r_id);
                remover_id(&L,r_id);
                break;
            case 4:
                mostrar(&L,n);
                break;
            //case 5:
                //printf("Digite o valor a ser inserido: ");
                //scanf("%d", &n.num);
                //printf("posicao para inserir: ");
                //scanf("%d", &position);
                //for(int i = j; i <= 50; i++){
                //    n.id = i;
                //    j++;
                //    break;
                //}
                //inserir_posicao(&L, n,position);
                //break;
            case 0:
                printf("FIM...\n");
                break;
            case 3:
                 if (lista_vazia(&L)) {
                  printf("A fila está vazia.\n");
                  break;
                }
                printf("qual posicao para remover:");
                scanf("%d", &r_posicao);
                remover_posicao(&L,r_posicao);
                break;
        }
    } while (comando != 0);

    return 0;
}
