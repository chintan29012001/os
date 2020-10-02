CC=gcc


parent:		parent.o		
	$(CC) parent.o -o parent
	echo compilation completed	
	echo waiting
	read a
	./parent

parent.o:	parent.s

	gcc -c parent.s -o parent.o
	echo assembled code
	echo waiting
	read a
	

parent.s:	parent.i 

	$(CC) -S parent.i -o parent.s
	echo compiled code
	echo waiting
	read a

parent.i:	parent.c

	$(CC) -E parent.c -o parent.i
	echo preprocessed code
	echo waiting
	read a

clean:
	rm -f parent.o
	rm -f parent.i
	rm -f parent.s
	rm -f parent
	




	


