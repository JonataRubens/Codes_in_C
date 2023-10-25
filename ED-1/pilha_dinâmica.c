#include <stdio.h>

typedef struct{
  int n;
  int id;
}dados;

typedef struct estru{
  dados conteudo;
  struct estru *ant;
}no;

typedef struct{
  no *topo;
}pilha;

int fila_cheia(pilha *p){
  
}

void empilha(pilha *p,dados n){
  if(fila_cheia(p)){
    printf('fila cheia');
  } else {
    //1 declara um ponteiro para o nó aux
    no* aux;
    //2 aloca o nó aux na memória
    aux = (no*)malloc(sizeof(no));
    aux->conteudo = n;
    aux.ant -> p.topo;
  }
}

void desempilha(pilha *p){
  
}

int main(void) {


}