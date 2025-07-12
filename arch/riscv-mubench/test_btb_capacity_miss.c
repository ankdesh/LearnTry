#include <stdio.h>

// NOTE: This number should be larger than the expected number of BTB entries.
#define NUM_FUNCS 32

// Define an array of functions to serve as unique branch targets.
#define DEF_FUNC(n) __attribute__((noinline)) void func_##n() { asm volatile("nop"); }
DEF_FUNC(0) DEF_FUNC(1) DEF_FUNC(2) DEF_FUNC(3) DEF_FUNC(4) DEF_FUNC(5) DEF_FUNC(6) DEF_FUNC(7)
DEF_FUNC(8) DEF_FUNC(9) DEF_FUNC(10) DEF_FUNC(11) DEF_FUNC(12) DEF_FUNC(13) DEF_FUNC(14) DEF_FUNC(15)
DEF_FUNC(16) DEF_FUNC(17) DEF_FUNC(18) DEF_FUNC(19) DEF_FUNC(20) DEF_FUNC(21) DEF_FUNC(22) DEF_FUNC(23)
DEF_FUNC(24) DEF_FUNC(25) DEF_FUNC(26) DEF_FUNC(27) DEF_FUNC(28) DEF_FUNC(29) DEF_FUNC(30) DEF_FUNC(31)

// Create an array of function pointers.
void (*func_pointers[NUM_FUNCS])() = {
    func_0, func_1, func_2, func_3, func_4, func_5, func_6, func_7,
    func_8, func_9, func_10, func_11, func_12, func_13, func_14, func_15,
    func_16, func_17, func_18, func_19, func_20, func_21, func_22, func_23,
    func_24, func_25, func_26, func_27, func_28, func_29, func_30, func_31
};

const int num_iters = 100;

int main() {
    volatile int i;
    // A lot of BTB misses
    for (i = 0; i < NUM_FUNCS * num_iters; i++) {
        func_pointers[i%NUM_FUNCS]();
    }

    return 0;
}
