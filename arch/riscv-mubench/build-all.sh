for file in *.c; do
  riscv64-unknown-elf-gcc -static -O0 -o "${file%.c}.out" "$file"
done
