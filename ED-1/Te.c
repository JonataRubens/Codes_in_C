#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int PA, PB;
        double G1, G2;
        int anos = 0;

        scanf("%d %d %lf %lf", &PA, &PB, &G1, &G2);

        while (PA <= PB) {
            PA += (int)(PA * G1 / 100.0);
            PB += (int)(PB * G2 / 100.0);
            anos++;

            if (anos > 100) {
                printf("Mais de 1 seculo.\n");
                break;
            }
        }

        if (anos <= 100) {
            printf("%d anos.\n", anos);
        }
    }

    return 0;
}
