for file in *.c; do
  riscv64-unknown-elf-gcc -static -O0 -S "${file%.c}.s" "$file"
done


# -ffunction-sections tells the compiler to put each function in its own section.
for file in test_icache*.c; do 
  riscv64-unknown-elf-gcc -ffunction-sections -static -O0 -S "${file%.c}.s" "$file"
done
