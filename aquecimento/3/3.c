#include <stdio.h>

int main() {
    int k, i, j, n, soma;
    scanf("%d", &k);
    i = 0;
    n = 6;

    while (i < k) {
        soma = 0;
        for (j = 1; j <= n / 2; j++) {
            if (n % j == 0) {
                soma += j;
            }
        }
        if (soma == n) {
            printf("%d ", n);
            i++;
        }
        n++;
    }
    printf("\n");

    return 0;
}
