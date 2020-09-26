final: sum32 sum64
	echo "compilation complete"
sum32: long_add32.o P4.c
	gcc -m32 P4.c long_add32.o -o sum32
long_add32.o: P4_1.asm
	nasm -felf32 P4_1.asm -o long_add32.o

sum64: long_add64.o P4.c
	gcc P4.c long_add64.o -o sum64
long_add64.o: P4_2.asm
	nasm -felf64 P4_2.asm -o long_add64.o
clean:
	rm -f long_add32.o
	rm -f sum32
	rm -f long_add64.o
	rm -f sum64
	