for file in test_b*.c; do 
  riscv64-unknown-elf-gcc -static -O0 -o "${file%.c}.out" "$file"
done

# -ffunction-sections tells the compiler to put each function in its own section.
for file in test_icache*.c; do 
  riscv64-unknown-elf-gcc -ffunction-sections -static -O0 -o "${file%.c}.out" "$file"
done
