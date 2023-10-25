#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

typedef struct{
    char nome[N];
    int idade;
    float peso;
    int grav;
}Nodo;

typedef struct{
    Nodo elementos[N];
    Nodo verde[N];
    Nodo amarelo[N];
    Nodo vermelho[N];
    int inicio,fim;
}Fila;

void inicia_fila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
}
void alerta(){
    printf("sinal de alerta p vermelho");
}

int fila_cheia(Fila f){
    return (f.fim + 1) % N == f.inicio;
}

int fila_vazia(Fila f){
    return f.inicio == f.fim;
}

void insere_fila(Fila *f, Nodo n, int *contador,int *ver,int *ama,int *verm){
    
    if(fila_cheia(*f)){
        printf("ERRO: fila cheia\n");
        return;
    }
    if(*contador == N){
        printf("ERRO: fila cheia\n");
        return;
    }
    //0 verde, 1 amarelo e 2 vermelho,
    if (n.grav == 0){
        f->verde[*ver] = n;
        (*ver)++;
    } else if (n.grav == 1){
        f->amarelo[*ama] = n;
        (*ama)++;
    } else {
        alerta();
        f->vermelho[*verm] = n;
        (*verm)++;
    }
    
    f->elementos[f->fim] = n;
    f->fim = (f->fim + 1) % N;
    (*contador)++;
}

Nodo remove_fila(Fila *f){
    if(fila_vazia(*f)){
        printf("ERRO: lista vazia");
        Nodo nodovazio = {"",0,0.0,0};
        return nodovazio;
    }
    if(f->elementos[f->inicio].grav == 0){
        f->verde[f->inicio] = f->verde[f->inicio + 1];
    } else if (f->elementos[f->inicio].grav == 1){
        f->amarelo[f->inicio] = f->amarelo[f->inicio+ 1];
    } else {
         f->vermelho[f->inicio] = f->vermelho[f->inicio+ 1];
    }

    Nodo nodo_removido = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % N;
    return nodo_removido;
}
void mostrar(Fila f){
    printf("\nLISTA DOS verdes\n");
    for(int i = f.inicio; i <= f.fim-1; i++){
        printf("nome:%s idade:%d peso:%2.f gravidade:%d\n", f.verde[i].nome,f.verde[i].idade,f.verde[i].peso,f.verde[i].grav);
    }
    printf("\nLISTA DOS amarelos\n");
    for(int i = f.inicio; i <= f.fim-1; i++){
        printf("nome:%s idade:%d peso:%2.f gravidade:%d\n", f.amarelo[i].nome, f.amarelo[i].idade, f.amarelo[i].peso, f.amarelo[i].grav);
    }
    printf("\nLISTA DOS VERMELHOS\n");
    for(int i = f.inicio; i <= f.fim-1; i++){
        printf("nome:%s idade:%d peso:%2.f gravidade:%d\n", f.vermelho[i].nome,f.vermelho[i].idade,f.vermelho[i].peso,f.vermelho[i].grav);
    }
}
int buscar_nome(Fila f,int cont, char nome[]){
    for(int i = 0; i < cont; i++){
        if(strcmp(f.elementos[i].nome, nome) == 0){
            return 1;
        }
    }
    return 0;
}

int main(void){

int count = 0,count_ver = 0,count_ama = 0,count_verm = 0,opcao;
Fila fila;
Nodo nodo;
char nome[N];

inicia_fila(&fila);

do{
        printf("\n1 - Inserir um nó\n");
        printf("2 - Remover um nó\n");
        printf("3 - Mostrar\n");
        printf("4 - Buscar\n");
        printf("0 - Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o nome: ");
                scanf(" %s", nodo.nome);
                printf("Digite o idade: ");
                scanf(" %d", &nodo.idade);
                printf("Digite o peso: ");
                scanf(" %f", &nodo.peso);
                printf("Gravidade: ");
                scanf(" %d", &nodo.grav);
                insere_fila(&fila , nodo, &count, &count_ver, &count_ama, &count_verm);
                break;
            case 2:
                Nodo nodo_removido = remove_fila(&fila);
                if(nodo_removido.idade > 0){
                    printf("Nodo removido: %s, %d anos, peso:%2.f Kilos, gravidade:%d\n", nodo_removido.nome, nodo_removido.idade,nodo_removido.peso, nodo_removido.grav);
                }
                break;
            case 3:
                mostrar(fila);
                break;
            case 4:
                printf("qual o nome: ");
                scanf("%s", &nome);
                if(buscar_nome(fila, count, nome)==1){
                    printf("o nome está na fila\n");
                } else {
                    printf("nao esta na lista\n");
                }
        }
} while(opcao != 0);

}