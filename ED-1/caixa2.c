#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max 11
#define Max_caixas 3

typedef struct Dados_clientes{
    char nome[50];
    int id;
    int prioridade; 
}Dados;

typedef struct Caixas{
    int numero;
    char status[70];
}Caixa;

typedef struct Gaveta{
    Dados clientes[Max];
    Dados C_priori[Max];
    Caixa caixas[Max_caixas];
    int inicio,fim,count,inicioP,fimP,priori;
}Agencia;

void inicia_tudo(Agencia* agencia){
    for(int i = 0; i <= Max_caixas; i++){
        strcpy(agencia->caixas[i].status, "fechado");
        agencia->caixas[i].numero = i+1;
    }
    agencia->inicio = 0;
    agencia->fim = 0;
    agencia->count = 0;
    agencia->inicioP= 0;
    agencia->fimP= 0;
}

int fila_vazia(Agencia agencia){
    if (agencia.fim == agencia.inicio && agencia.fimP == agencia.inicioP){
        printf("A fila está vazia\n");
        return 1;
    }
    return 0;
}
int Fila_cheia(Agencia agencia){
   if(agencia.count+1 == Max){
     printf("\nA fila está cheia\n");
     return 1;
   }
  return 0;
}
void Fecha_caixa(Agencia* agencia,int numCaixa){
        strcpy(agencia->caixas[numCaixa-1].status, "fechado");
}
void abre_caixa(Agencia* agencia,int ncaixa){
    strcpy(agencia->caixas[ncaixa-1].status, "livre");
}

void Chega_cliente(Agencia* agencia, Dados dados) {
    if(Fila_cheia(*agencia)){
      printf("\nFila cheia\n");
        return;
    }
    int caixa_disponivel = -1;
    for (int i = 0; i < Max_caixas; i++) {
        if (strcmp(agencia->caixas[i].status, "livre") == 0) {
            caixa_disponivel = i;
            break;
        }
    }
    if(agencia->count > 0){ 
        if (dados.prioridade == 0) {
            agencia->clientes[agencia->fim] = dados;
            agencia->fim = (agencia->fim + 1) % Max;
            printf("O cliente %s entrou na fila de espera.\n", dados.nome);
            agencia->count++;
            return;
        } else {
            agencia->C_priori[agencia->fimP] = dados;
            agencia->fimP = (agencia->fimP + 1) % Max;
            agencia->priori++;
            printf("O cliente %s entrou na fila de prioridade.\n", dados.nome);
            agencia->count++;
            return;
        }
    }
    if (caixa_disponivel == -1){
        if (dados.prioridade == 0) {
            agencia->clientes[agencia->fim] = dados;
            agencia->fim = (agencia->fim + 1) % Max;
            printf("O cliente %s entrou na fila de espera.\n", dados.nome);
        } else {
            agencia->C_priori[agencia->fimP] = dados;
            agencia->fimP = (agencia->fimP + 1) % Max;
            agencia->priori++;
            printf("O cliente %s entrou na fila de prioridade.\n", dados.nome);
        }
        agencia->count++;
    } else {
        strcpy(agencia->caixas[caixa_disponivel].status, "Ocupado pelo cliente ");
        strcat(agencia->caixas[caixa_disponivel].status, dados.nome);
        printf("O cliente %s foi atendido pelo caixa %d.\n", dados.nome, caixa_disponivel + 1);
    }
}
void Caixa_livre(Agencia* agencia, Dados dados){
    if(fila_vazia(*agencia)){
      return;
    }
    int j=0;
    for(int i = 0; i <= Max_caixas; i++){
        if(strcmp(agencia->caixas[i].status,"livre") == 0){
            j++;
        }
    }
    if(j == 0){
        printf("\ntodos os caixas estao ocupados ou fechados\n");
        return;
    }
    for(int i = 0; i < Max_caixas; i++){
        if(strcmp(agencia->caixas[i].status,"livre") == 0){
            if(agencia->priori > 0){
                strcpy(agencia->caixas[i].status, "Ocupado pelo cliente ");
                strcat(agencia->caixas[i].status, agencia->C_priori[agencia->inicioP].nome);
                agencia->priori--;
                agencia->count--;
                agencia->inicioP = (agencia->inicioP + 1) % Max;
                //return;
            } else {
                strcpy(agencia->caixas[i].status, "Ocupado pelo cliente ");
                strcat(agencia->caixas[i].status, agencia->clientes[agencia->inicio].nome);
                agencia->count--;
                agencia->inicio = (agencia->inicio + 1) % Max;
                //return;
            }
        }
    }
}

void Sai_cliente(Agencia* agencia) {
    if(fila_vazia(*agencia)){
      return;
    }
    int id_c, i, j;
    printf("Qual o ID do cliente?");
    scanf("%i", &id_c);

    for (i = agencia->inicioP; i != agencia->fimP; i = (i + 1) % Max) {
        if (agencia->C_priori[i].id == id_c) {
            j = i;
            while (j != agencia->fimP) {
                agencia->C_priori[j] = agencia->C_priori[(j + 1) % Max];
                j = (j + 1) % Max;
            }
            agencia->fimP = (agencia->fimP - 1) % Max;
            agencia->count--;
            agencia->priori--;
            return;
        }
    }
  int x;
    for (x = agencia->inicio; x != agencia->fim; x = (x + 1) % Max) {
          if (agencia->clientes[x].id == id_c) {
              j = x;
              while (j != agencia->fim) {
                  agencia->clientes[j] = agencia->clientes[(j + 1) % Max];
                  j = (j + 1) % Max;
              }
              agencia->fim = (agencia->fim - 1) % Max;
              agencia->count--;
              return;
          }
      }
    return;
}
void mostra_caixas_filas(Agencia agencia){
    printf("\n\nStatus dos caixas:\n");
    for(int i = 0; i < Max_caixas; i++){
        printf("Caixa %d: %s\n", agencia.caixas[i].numero, agencia.caixas[i].status);
    }
    printf("\n\nFila normal:\n");
    int i = agencia.inicio;
    while(i != agencia.fim){
        printf("NOME: %s ID:%d\n", agencia.clientes[i].nome, agencia.clientes[i].id);
        i = (i + 1) % Max;
    }
    printf("\n\nFila prioritaria:\n");
    i = agencia.inicioP;
    while(i != agencia.fimP){
        printf("NOME: %s ID:%d\n", agencia.C_priori[i].nome, agencia.C_priori[i].id);
        i = (i + 1) % Max;
    }
    printf("\n\n============================\ninicioP: %i  ____  fimP: %i\ninicio: %i  ____  fim: %i\n\n",agencia.inicioP,agencia.fimP,agencia.inicio,agencia.fim);
}


int main(void){
    int opcao,numCaixa,i,j=1,ncaixa,id_c;
    
    Agencia agencia;
    Dados dados;
    Caixa caixas;

    inicia_tudo(&agencia);

    do{
        printf("\n1: cliente chega\n2: fecha caixa\n3: caixa livre\n4: tira cliente\n5: mostrar tudo\n6: abre caixa\n0: sair\n");
        scanf("%i",&opcao);

        switch(opcao){
            case 1:
            if(Fila_cheia(agencia)){
                break;
            }
                printf("nome: ");
                scanf("%s",dados.nome);
                for(i = j; i <= 50; i++){
                    dados.id = i;
                    j++;
                    break;
                }
                printf("prioridade: ");
                scanf("%d",&dados.prioridade);
                Chega_cliente(&agencia, dados);

            break;
            case 2:
                printf("qual caixa para fechar 1,2 ou 3?: ");
                scanf("%i",&numCaixa);
                Fecha_caixa(&agencia,numCaixa);

            break;
            case 3:
                Caixa_livre(&agencia,dados);

            break;
            case 4:
                Sai_cliente(&agencia);
              
            break;
            case 5:
            mostra_caixas_filas(agencia);

            break;
            case 6:
            printf("liberar qual? ");
            scanf("%d",&ncaixa);
            abre_caixa(&agencia,ncaixa);

            break;
        }
    }while(opcao != 0);

}