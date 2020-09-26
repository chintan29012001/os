final: withoutc withc withoutc1 withc1 
	echo "compilation complete"
withc: withc.o assembly.o
	gcc  withc.o assembly.o -o withc
withc.o:withc.c
	gcc -c withc.c -o withc.o
withoutc : assembly.o
	ld -e start assembly.o -o withoutc
assembly.o: assembly.asm
	nasm -felf64 assembly.asm -o assembly.o
withc1: withc.o assembly1.o
	gcc  withc.o assembly1.o -o withc1
withoutc1 : assembly1.o
	ld -e _start assembly1.o -o withoutc1
assembly1.o: assembly1.asm
	nasm -felf64 assembly1.asm -o assembly1.o

clean:
	rm -f assembly.o
	rm -f assembly1.o
	rm -f withoutc
	rm -f withoutc1
	rm -f withc.o
	rm -f withc
	rm -f withc1