#include <stdio.h>
#include <stdlib.h>
#define N 50

typedef struct{
    char nome[N];
    int idade;
    int codigo;
}Nodo;

typedef struct{
    Nodo elementos[N];
    int inicio;
    int fim;
}Fila;

int inicia_fila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
}

int fila_cheia(Fila f){
    return (f.fim + 1) % N == f.inicio;
}

int fila_vazia(Fila f){
    return f.inicio == f.fim;
}

void insere_fila(Fila *f, Nodo n){
    if(fila_cheia(*f)){
        printf("ERRO: fila cheia\n");
        return;
    }
    f->elementos[f->fim] = n;
    f->fim = (f->fim + 1) % N;
}

Nodo remove_fila(Fila *f){
    if(fila_vazia(*f)){
        printf("ERRO: lista vazia");
        Nodo nodovazio = {"",0,0};
        return nodovazio;
    }
    Nodo nodo_removido = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % N;
    return nodo_removido;
}

int main(void){

int opcao;
Fila fila;
Nodo nodo;

inicia_fila(&fila);

do{
        printf("\n1 - Inserir um nó\n");
        printf("2 - Remover um nó\n");
        printf("0 - Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o nome: ");
                scanf("%s", nodo.nome);
                printf("Digite o idade: ");
                scanf("%d", &nodo.idade);
                printf("Digite o codigo: ");
                scanf("%d", &nodo.codigo);
                insere_fila(&fila , nodo);
                break;
            case 2:
                Nodo nodo_removido = remove_fila(&fila);
                if(nodo_removido.idade > 0){
                    printf("Nodo removido: %s, %d anos, código %d\n", nodo_removido.nome, nodo_removido.idade, nodo_removido.codigo);
                }
                break;
            case 0:
                printf("Saindo do programa\n");
                break;
            default:
                printf("Opção inválida\n");
        }
} while(opcao != 0);

}


