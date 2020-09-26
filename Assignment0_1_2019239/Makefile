CC=gcc


hello:		hello.o		
	$(CC) hello.o -o hello
	echo compilation completed	
	echo waiting
	read a
	./hello

hello.o:	hello.s

	gcc -c hello.s -o hello.o
	echo assembled code
	echo waiting
	read a
	

hello.s:	hello.i 

	$(CC) -S hello.i -o hello.s
	echo compiled code
	echo waiting
	read a

hello.i:	hello.c

	$(CC) -E hello.c -o hello.i
	echo preprocessed code
	echo waiting
	read a

clean:
	rm -f hello.o
	rm -f hello.i
	rm -f hello.s
	rm -f hello
	




	



