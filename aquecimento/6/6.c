#include <stdio.h>

int main() {
    int n, i, penultimo, ultimo, atual, soma_n_fibonacci;
    soma_n_fibonacci = 1;
    penultimo = 0;
    ultimo = 1;
    atual = 1;
    i = 2;

    scanf("%d", &n);

    while (i < n) {
        soma_n_fibonacci += atual;
        penultimo = ultimo;
        ultimo = atual;
        atual = penultimo + ultimo;
        i++;
    }

    printf("%d\n", soma_n_fibonacci);

    return 0;
}
