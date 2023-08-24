#include <stdio.h>

int main() {
    int n, q, ehSerie;
    ehSerie = 1;
    
    do {
        scanf("%d", &n);
        if (n != 0) {
            scanf("%d", &q);
            if (n * n != q) {
                ehSerie = 0;
            }
        }
    } while (n != 0);

    printf("%d\n", ehSerie);

    return 0;
}
