ENTRY(main)
MEMORY { RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 256M }

/* Define the global pointer, required by the RISC-V toolchain */
__global_pointer$ = .;

SECTIONS {
  /*
   * --- A More Explicit Approach ---
   * Define each section with its target VMA (Virtual Memory Address)
   * directly in the section header. This is a more robust syntax.
   */
  .conflict_A_sec 0x140 : { *(conf_A) } > RAM
  .conflict_B_sec 0x2140 : { *(conf_B) } > RAM
  .conflict_C_sec 0x4140 : { *(conf_C) } > RAM
  .conflict_D_sec 0x6140 : { *(conf_D) } > RAM
  .conflict_E_sec 0x8140 : { *(conf_E) } > RAM

  /* --- Place all remaining standard sections after our custom ones. --- */
  /* The linker will place this starting after the last custom section,
     or at the next available address if there's a gap. */
  .text : {
    *(.text .text.*)
    *(.rodata .rodata.*)
  } > RAM

  .data : { *(.data .data.*) } > RAM

  /* Define __bss_start and _end symbols */
  __bss_start = .;
  .bss  : { *(.bss .bss.*)  } > RAM
  _end = .;
}
