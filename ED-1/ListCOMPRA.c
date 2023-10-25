#include <stdio.h>

int main()

{
    
char list[10], rem;
int add, j, i=0, x, k, item,opcao = 1;

while (1){
    printf("\n ===menu=== \n"); 
    scanf("%d", &add);
    if (add == 1){
        i += 1;
        printf("digite o item: ");
        scanf(" %c", &list[i]);
    }
    else if(add == 2){
        printf("digite o item para ser removido: \n-->");
        scanf(" %c", &rem);
        for(x=0; x<=i; x++){
          if (rem == list[x]){
            item = x;
            break;
          }
        }
        for (j=x; j<=i ;j++){
            list[j] = list[j+1];
        }
      }
    else if(add == 3){
      printf("a lista eh \n --> ");
      for(k=0; k<=i; k++){
        printf("%c ",list[k]);
      }
    }

    else 
        break;
}

return 0;
}