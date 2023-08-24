#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d", &a);
    b = a * 37;
    c = 0;

    while (b != 0) {
        c += b % 10;
        b /= 10;
    }

    if (a == c) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

    return 0;
}
