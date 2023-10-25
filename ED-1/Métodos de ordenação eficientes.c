#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int particao(int vet[], int inicio, int fim){
  int pivo = vet[fim];
  int i = (inicio -1);
  for(int j = inicio; j <= fim - 1; j++){
    if (vet[j] < pivo) {
            i++;
            swap(&vet[i], &vet[j]);
        }
    }
    swap(&vet[i + 1], &vet[fim]);
    return (i + 1);  
}

void quick_sort(int vet[], int inicio, int fim){
  if(inicio < fim){
    int arr = particao(vet, inicio, fim);
    quick_sort(vet,inicio,fim - 1);
    quick_sort(vet,arr + 1,fim);
  }
}

int main(void) {
  int vetor[] = {21, 20, 11, 22, 8, 12, 4, 17, 9, 1, 7, 3, 16, 10, 23, 6, 14, 25, 18, 5, 24, 15, 13, 2, 19};
  int n = sizeof(vetor) / sizeof(vetor[0]);
    quick_sort(vetor, 0, n - 1);
    printf("vetor ordenado: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);
    return 0;

}

