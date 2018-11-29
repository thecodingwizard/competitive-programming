#include <iostream>
#include <cstring>

int main() {
    int duration, recordCount, index, months;
    double down, loan, value;
    float depreciation[110] = {0};
    float amount;
    while (scanf("%d %lf %lf %d", &duration, &down, &loan, &recordCount) && duration >= 0) {
        while (recordCount-- > 0) {
            scanf("%d %f", &index, &amount);
            depreciation[index] = amount;
        }
        for (int i = 0; i < 103; i++) {
            if (depreciation[i] == 0.0) depreciation[i] = depreciation[i - 1];
        }
        value = (loan + down) * (1 - depreciation[0]);
        amount = loan/duration;
        for (months = 1; loan >= value; months++) {
            loan -= amount;
            value *= (1.0 - depreciation[months]);
        }
        months--;
        if (months == 1) printf("%d month\n", months);
        else printf("%d months\n", months);
        memset(depreciation, 0, sizeof(depreciation));
    }

    return 0;
}