#include <stdio.h>

int main() {
    int x, y, q, s;
    scanf("%d", &y);
    q = 1;
    s = y;

    while (1) {
        x = y;
        scanf("%d", &y);
        s += y;
        q++;

        if (y == x * 2 || y == x / 2) {
            break;
        }
    }

    printf("%d %d %d %d\n", q, s, x, y);

    return 0;
}
