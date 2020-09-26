add: add1.o add2.o
	gcc add1.o add2.o -o add
	echo compilation completed	
	echo waiting
	read a
	./add
add1.o: add.asm
	nasm -felf64 add.asm -o add1.o
	echo assembled code	
	read a
add2.o: add.s
	gcc -c add.s -o add2.o
	echo assembled code	
	read a
add.s:	add.i 

	$(CC) -S add.i -o add.s
	echo compiled code
	echo waiting
	read a

add.i:	add.c
	
	$(CC) -E add.c -o add.i
	echo preprocessed code	
	echo waiting
	read a
	
clean:
	rm -f add1.o
	rm -f add.i
	rm -f add.s
	rm -f add2.o
	rm -f add
