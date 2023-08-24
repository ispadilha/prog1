#include <stdio.h>

int main() {
    int a, b, c, n, flag;
    scanf("%d", &n);
    flag = 0;
    a = 1;
    b = 2;
    c = 3;

    while (c <= n / 2) {
        if (a * b * c == n) {
            flag = 1;
        }
        a = b;
        b = c;
        c = c + 1;
    }

    printf("%d\n", flag);

    return 0;
}
