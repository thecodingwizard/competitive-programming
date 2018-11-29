#include <iostream>

int main() {
    int t;
    long a, b;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%ld %ld", &a, &b);
        if (a == b) printf("=\n");
        else printf(a > b ? ">\n" : "<\n");
    }

    return 0;
}