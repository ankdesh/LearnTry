#include <stdio.h>

// --- Local Cache Configuration ---
#define ICACHE_SIZE         (64 * 1024)
#define CACHE_LINE_SIZE     64
#define ASSOCIATIVITY       4

// A function of 64 bytes
#define DEFINE_CAPACITY_FUNC(n) \
    void __attribute__((section(".capacity_funcs"))) capacity_func_##n() { \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
        __asm__ __volatile__("nop;"); \
    }

// Each of above function gets converted to 64 bytes function shown below
//capacity_func_1:
//        addi    sp,sp,-16
//        sd      ra,8(sp)
//        sd      s0,0(sp)
//        addi    s0,sp,16
//        nop;
//        nop;
//        nop;
//        nop;
//        nop;
//        nop;
//        nop;
//        nop;
//        ld      ra,8(sp)
//        ld      s0,0(sp)
//        addi    sp,sp,16
//        jr      ra
//        .size   capacity_func_1, .-capacity_func_1
//        .align  1
//        .globl  capacity_func_2
//        .type   capacity_func_2, @function



// Define enough functions to overflow a 64KB cache.
// 64KB / 64 = 1000 entries
#include "thousand_functions.h"

// Create an array of pointers to these functions.
#include "thousand_functions_array.h"

void main() {
    printf("\nCapacity Miss Test --- \n");

    // Access all 1000 lines
    for (int i = 0; i < 1000; ++i) {
        capacity_test_funcs[i]();
    }
    // This should be a miss
    capacity_func_1();
}

