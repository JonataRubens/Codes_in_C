/************************ PILHA ESTÁTICA ***************************************/
#include <stdio.h>

#define N 100

typedef int no;

typedef struct{
    no num[N];
    no topo;
}pilha;

/******************Operações aplicadas à pilha estática**********************/

void iniciaPilha(pilha *p);
char pilhaCheia(pilha p);
char pilhaVazia(pilha p);
void empilha(pilha *p, no n);
no desempilha(pilha *p);
int tamanho(pilha p);
int busca(pilha p, no n);
void mostra(pilha p);

void main(void){
  no numero,item;    
  char op;
  pilha PILHA1;
  iniciaPilha(&PILHA1);
  do{
      printf("\n[1] Inserir\n[2] Remover\n[3] buscar\n[4] sair\n:->");
      scanf(" %c", &op);
    switch(op){
      case '1':
        printf("digite o numero que deseja inserir:");
        scanf("%d", &numero);
        empilha(&PILHA1, numero);
        break;
      case '2':
        desempilha(&PILHA1);
        break;
      case '3':
        printf("\nItem a ser buscado:");
        scanf("%d", &item);
        if(busca(PILHA1,item)==1) printf("\n%d Esta na pilha\n============", item);
        else printf("\n%d Nao esta na pilha\n============", item);
        break;
        
    }
      mostra(PILHA1);
      tamanho(PILHA1);
  }while(op != '4');
}

void iniciaPilha(pilha *p){
    p->topo = 0;
}
char pilhaCheia(pilha p){
    if(p.topo >=N) return 1;
    return 0;
}
char pilhaVazia(pilha p){
    if(p.topo <= 0) return 1;
    return 0;
}
void empilha(pilha *p, no n){
    if(pilhaCheia(*p)){
      printf("Pilha Cheia! Não é possivel inserir============");
    }else{
      p->num[p->topo] = n;
      p->topo++;
    }
}
no desempilha(pilha *p){
    if (pilhaVazia(*p)==1){
        printf("\npilha vazia\n============");
        return 0;
        }
     p->num[p->topo-1] = p->num[p->topo];
     p->topo--;
     return 1;
}
int tamanho(pilha p){
    printf("\nTamanho da pilha: %d\n============", p.topo);
}
int busca(pilha p, no n){
   int i;
   for(i=0; i<p.topo; i++){
      if(p.num[i] == n)return 1;
   } 
}
void mostra(pilha p){
    printf("\nLista de nuns na pilha:\n");
    for(int i=0;i<p.topo;i++){
      printf("%d \n", p.num[i]);
    }
}