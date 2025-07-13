for file in test_*.c; do 
  riscv64-unknown-elf-gcc -static -O0 -o "${file%.c}.out" "$file"
done

# -ffunction-sections tells the compiler to put each function in its own section.
for file in ld_test*.c; do 
  riscv64-unknown-elf-gcc -static -nostdlib -fno-builtin -O0 -ffunction-sections  -o "${file%.c}.out" "$file" -T ${file%.c}.ld
done
