for file in *.c; do
  riscv64-unknown-elf-gcc -static -O0 -S "${file%.c}.s" "$file"
done
