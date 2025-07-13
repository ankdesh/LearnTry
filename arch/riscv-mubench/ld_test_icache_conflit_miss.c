// --- Local Cache Configuration ---
#define ICACHE_SIZE         (32 * 1024)
#define CACHE_LINE_SIZE     64
#define ASSOCIATIVITY       4

// Define ASSOCIATIVITY + 1 (5) functions to conflict in the same set.
void __attribute__((section("conf_A"))) conflict_func_A() { __asm__("nop"); }
void __attribute__((section("conf_B"))) conflict_func_B() { __asm__("nop"); }
void __attribute__((section("conf_C"))) conflict_func_C() { __asm__("nop"); }
void __attribute__((section("conf_D"))) conflict_func_D() { __asm__("nop"); }
void __attribute__((section("conf_E"))) conflict_func_E() { __asm__("nop"); }

const int num_iters = 1000;

// Linker script makes sure that all the functions are placed a addresses which map to same set
// Output of readelf
//    19: 0000000000008140    20 FUNC    GLOBAL DEFAULT    5 conflict_func_E
//    20: 0000000000002140    20 FUNC    GLOBAL DEFAULT    2 conflict_func_B
//    23: 0000000000004140    20 FUNC    GLOBAL DEFAULT    3 conflict_func_C
//    26: 0000000000006140    20 FUNC    GLOBAL DEFAULT    4 conflict_func_D
//    27: 0000000000000140    20 FUNC    GLOBAL DEFAULT    1 conflict_func_A

// Main entry point for this specific test.
void main() {
  for (int i = 0; i < num_iters; i++){
    conflict_func_A();
    conflict_func_B();
    conflict_func_C();
    conflict_func_D();
    conflict_func_E();
    conflict_func_A();
  }
}
