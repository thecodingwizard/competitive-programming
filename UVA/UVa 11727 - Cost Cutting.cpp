#include <iostream>
#include <algorithm>

int main() {
    int T, arr[3], i = 0;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
        std::sort(std::begin(arr), std::end(arr));
        printf("Case %d: %d\n", ++i, arr[1]);
    }
    return 0;
}