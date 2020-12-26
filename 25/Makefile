include ../Makefile.inc

main-asm.o: main.asm
	nasm -felf64 -o main-asm.o main.asm

main-libc: main-asm.o
	gcc -o main-libc main-asm.o

main-asm: main-asm.o
	ld -n -s -o main-asm -e main main-asm.o
