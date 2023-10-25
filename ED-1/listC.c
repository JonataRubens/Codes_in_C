/****** Lista de compras usando vetor *******/
#include <stdio.h>
#include <string.h>

#define N 10

typedef struct{
    char nome[15];
    int qtd;
}no;

typedef struct{
    no list[N];
    int fim;
}listaCompra;

listaCompra listaMercado;

/****** Protótipos das funções ********/
char inserir(listaCompra *, no);
char remover(listaCompra *, no);
void mostra(listaCompra);

 

void main(void){
    char op;
    no item;
    int v = 0;
    listaMercado.fim = 0;

    printf("\n[1] Inserir um item\n[2] Remover um item\n[3] Sair\n");
    scanf(" %s", &op);

    do{
            switch(op){
                case '1':
                    printf("\n\tItem a iserir: ");
                    scanf("%s", &item.nome);
                    printf("\n\t quantidade: ");
                    scanf("%d", &item.qtd);
                    if(inserir(item.nome) == 0){
                      printf("\nlista cheia\n");
                    }
                    break;
                case '2':
                    printf("digite o item para ser removido: \n--> ");
                    scanf("%s", &item.nome);
                    if(remover(&listaMercado, item) == 0){
                      printf("item nao encontrado");
                      }
   
            }
            mostra(listaMercado);
            printf("\n[1] Inserir um item\n[2] Remover um item\n[3] Sair\n");
            scanf(" %s", &op);
    }while(op != '3');
}

char inserir(listaCompra *l,no valor){
    if(l->fim == N) return 0;
  
    l->list[l->fim] = valor;
    l->fim++;
    return 1;
 
}
char remover(listaCompra *l,no rem){
    int a=0;
    if(l->fim == 0) return(0);
    
    int i,j;
    for (i = 0; i< l->fim; i++)
        if(strcmp(l->list[i].nome, rem.nome) == 0) break;

    for(i=0; i<= l->fim; i++){
          if(rem == l->list[i]) {
            a = 0;
            break;
            
          }else{
          a = 1;
        }
        }
        if (a == 1) return 0;
  
          for (int j=i; j< l->fim ;j++){
            l->list[j] = l->list[j+1];
          }
  
  }
 
void mostra(listaCompra l){
    if(l.fim == 0)
        printf("\nLista vazia");
    else{
        int i;
        printf("\nLista:");
        for (i = 0; i<l.fim;i++) printf("\n\t %s %d", l.list[i].nome, l.list[i].qtd);
        printf("\n");
    }
}