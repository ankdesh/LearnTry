ENTRY(main)

MEMORY {
    /* Use a single, unified memory region for this self-contained test.
       While RWX permissions generate a warning, it is acceptable for this
       specific simulation where functionality, not security, is the focus. */
    MEM (rwx) : ORIGIN = 0x00000000, LENGTH = 256M
}

SECTIONS {
  /* Place all sections into the single MEM region */
  .text : {
    *(.text .text.*)
    *(.rodata*)
  } > MEM

  .jump_A 0x40000 : { *(.jump_A) } > MEM
  .jump_B 0x50000 : { *(.jump_B) } > MEM
  .jump_C 0x60000 : { *(.jump_C) } > MEM

  /* Place data, including the jump_table, in the same region */
  .data : {
    *(.data)
  } > MEM

  .bss : {
    *(.bss)
  } > MEM
}
