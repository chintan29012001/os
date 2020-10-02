CC=gcc


shell:	shell.c cd.h echo.h history.h ls cat date rm mkdir		
	$(CC) shell.c -o shell

ls: ls.c
	$(CC) ls.c -o ls
cat: cat.c
	$(CC) cat.c -o cat
date: date.c
	$(CC) date.c -o date
rm: rm.c
	$(CC) rm.c -o rm
mkdir: mkdir.c
	$(CC) mkdir.c -o mkdir



clean:
	rm -f ./shell
	rm -f ./mkdir
	rm -f ./ls
	rm -f ./cat
	rm -f ./date
	rm -f ./rm




	

