#include <stdio.h>
#include <string.h>
#define Max 9
#define Max_caixas 3

typedef struct Dados_clientes{
    char nome[50];
    int id;
    int prioridade; // 0 sem prio, 1 com.02/05
}Dados;

typedef struct Caixas{
    int numero;
    char status[50];
}Caixa;

typedef struct Gaveta{
    Dados clientes[Max];
    Dados C_priori[Max];
    Caixa caixas[Max_caixas];
    int numClientes,numC_prioridade,count;
}Agencia;

void inicia_tudo(Agencia* agencia){
    for(int i = 0; i <= Max_caixas; i++){
        strcpy(agencia->caixas[i].status, "fechado");
        agencia->caixas[i].numero = i+1;
    }
    agencia->numClientes = 0;
    agencia->numC_prioridade = 0;
    agencia->count = 0;
}

int Fila_vazia(Agencia agencia){
    return agencia.count == 0;
}

int Fila_cheia(Agencia agencia){
    return agencia.count == Max;
}
void Caixa_livre(Agencia* agencia){
    //verifica se á caixa livre se sim, pega o primeiro da fila e aloca o restante para frete
    if(Fila_vazia(*agencia)){
        printf("fila vazia");
        return;
    }
    int i;
    for (i = 0; i < Max_caixas; i++){
        if(strcmp(agencia->caixas[i].status, "livre") == 0){
            //se tiver pessoas na fila entra
                if(agencia->numC_prioridade > 0){
                    strcpy(agencia->caixas[i].status, "Ocupado com o cliente ");
                    strcat(agencia->caixas[i].status, agencia->C_priori[0].nome);
                    int j;
                    for(j = 0; j <= agencia->numC_prioridade; j++){
                        agencia->C_priori[j] = agencia->C_priori[j+1];
                    }
                    agencia->count--;
                    agencia->numC_prioridade--;
                    break;

                } else { 
                        strcpy(agencia->caixas[i].status, "Ocupado com o cliente ");
                        strcat(agencia->caixas[i].status, agencia->clientes[0].nome);
                        int j;
                        for(j = 0; j <= agencia->numClientes; j++){
                            agencia->clientes[j] = agencia->clientes[j+1];
                        }
                        agencia->count--;
                        agencia->numClientes--;
                        break;

                }

        } else {
            strcpy(agencia->caixas[i].status, "livre");
        }
    }
    return;
    
}

void Fecha_caixa(Agencia* agencia,int numCaixa){
    strcpy(agencia->caixas[numCaixa-1].status, "fechado");

}

void Chega_cliente(Agencia* agencia, Dados dados){
    int i;
    // for para ver se tem caixa livre 
    for(i = 0; i <= Max_caixas; i++){
        if(strcmp(agencia->caixas[i].status, "livre") == 0){

            strcpy(agencia->caixas[i].status, "Ocupado pelo cliente ");
            strcat(agencia->caixas[i].status, dados.nome);
            return;
        }
    }
    //se nao tiver livre poem o cliente na fila.
    if(dados.prioridade == 0){
        agencia->clientes[agencia->numClientes] = dados;
        agencia->numClientes++;
    } else {
        agencia->C_priori[agencia->numC_prioridade] = dados;
        agencia->numC_prioridade++;
    }
    agencia->count++;
}

void Sai_cliente(Agencia* agencia){
    if(Fila_vazia(*agencia)){
        printf("fila vazia");
        return;
    }
    int id_c;
    printf("qual id do cliente?");
    scanf("%i", &id_c);
    int i, posi;
    //procurar nas filas
    for(int y = 0; y <= agencia->numC_prioridade; y++){
        if(agencia->C_priori[y].id == id_c){
            int j;
            posi = y;
            for(j = posi; j <= agencia->numC_prioridade; j++){
                agencia->C_priori[j] = agencia->C_priori[j+1];
            }
            agencia->numC_prioridade--;
            agencia->count--;
            return;
        }
    }

    for(int y = 0; y <= agencia->numClientes; y++){
        if(agencia->clientes[y].id == id_c){
            int j;
            posi = y;
            for(j =posi; j <= agencia->numClientes; j++){
                agencia->clientes[j] = agencia->clientes[j+1];
            }
            agencia->numClientes--;
            agencia->count--;
            return;
        }
    }
}


void mostra_caixas_filas(Agencia agencia) {
    printf("===== Caixas =====\n");
        printf("Caixa %d: %s\n", agencia.caixas[0].numero, agencia.caixas[0].status);
        printf("Caixa %d: %s\n", agencia.caixas[1].numero, agencia.caixas[1].status);
        printf("Caixa %d: %s\n", agencia.caixas[2].numero, agencia.caixas[2].status);
    
    printf("\n===== Fila Normal =====\n");
        for(int i = 0; i < agencia.numClientes; i++){
            printf("Posicao %d: %s (ID: %d)\n", i+1, agencia.clientes[i].nome,   agencia.clientes[i].id);
        }
    printf("\n===== Fila Prioritaria =====\n");
      for(int i = 0; i < agencia.numC_prioridade; i++){
            printf("Posicao %d: %s (ID: %d)\n", i+1, agencia.C_priori[i].nome,   agencia.C_priori[i].id);
}
}

int main(void){
    int opcao,numCaixa,i,j=1;
    
    Agencia agencia;
    Dados dados;
    Caixa caixas;

    inicia_tudo(&agencia);

    do{
        printf("\n1: cliente chega\n2: fecha caixa\n3: caixa livre\n4: tira cliente\n5: mostrar tudo\n0: sair\n");
        scanf("%i",&opcao);

        switch(opcao){
            case 1:
            if(Fila_cheia(agencia)){
                    printf("Fila cheia");
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
                Caixa_livre(&agencia);

            break;
            case 4:
                Sai_cliente(&agencia);
              
            break;
            case 5:
            mostra_caixas_filas(agencia);

            break;
        }
    }while(opcao != 0);

}