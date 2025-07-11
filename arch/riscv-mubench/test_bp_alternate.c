#include <stdio.h>

// Pattern: T, N, T, N, T, N, T, N, ...
const int pattern[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
const int pattern_len = sizeof(pattern) / sizeof(pattern[0]);
const int num_iter = 10000; 

int main() {
    volatile int i;
    int dummy = 0;

    for (i = 0; i < pattern_len * num_iter; i++) {
        if (pattern[i % pattern_len]) {
            dummy++;
        }
    }
    printf("Dummy value: %d\n", dummy);
    return 0;
}

