
#include <stdio.h>
#include <string.h>
#define N 100

typedef char no[30];

typedef struct{
    no num[N];
    int topo;
}pilha;

void iniciaPilha(pilha *p);
char pilhaCheia(pilha p);
char pilhaVazia(pilha p);
void empilha(pilha *p, no n);
void desempilha(pilha *p);
void mostra(pilha p);

void main(void){
  no op;
  pilha path;
  iniciaPilha(&path);
  while(1){
     printf("\n");
     mostra(path);
     printf(">");
    gets(op);
    if (strcmp(op,"path") == 0) printf("\npath: "), mostra(path), printf("\n");
        else
            if (strcmp(op, "exit") == 0) break;
                else  
                    if(op[0] == 'c' && op[1] == 'd')
                        if ((op[2] == '\\') || (op[2] == ' ' && op[3] == '\\'))
                            iniciaPilha(&path);
                        else
                            if ((op[2] == '.' && op[3] == '.') || (op[2] == ' ' && op[3] == '.' && op[4] == '.'))
                            desempilha(&path);
                            else{
                                int ini,i,j=0;
                                no nome;
                                if (op[2]== ' ') ini =3;
                                else ini = 2;
                                for (i = ini; op[i]!='\0'; i++)
                                    nome[j] = '\0';
                                    empilha(&path, nome);
                            }
                    else
                    printf("\ncomando desconhecido\n");

    }
                
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
      printf("Pilha Cheia! Não é possivel inserir");
    }else{
      strcpy(p->num[p->topo],n);
      p->topo++;
    }
}
void desempilha(pilha *p){
    if (!pilhaVazia(*p)){
        p->topo--;
    }
}

void mostra(pilha p){
    printf("C://");
    if (!pilhaVazia(p)){
        for(int i=0;i<p.topo;i++){
        printf("%s \n", p.num[i]);
        }
    }
}