for file in test_*.c; do 
  riscv64-unknown-elf-gcc -static -O0 -S "${file%.c}.s" "$file"
done

# -ffunction-sections tells the compiler to put each function in its own section.
for file in ld_test*.c; do 
  riscv64-unknown-elf-gcc -static -O0 -ffunction-sections  -S "${file%.c}.s" "$file" -T ${file%.c}.ld
done
