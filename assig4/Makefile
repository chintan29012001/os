final: block non_block

block_run: block
	./block
non_block_run: non_block
	./non_block
block: blocking_mutex2019239.c
	gcc  blocking_mutex2019239.c -lpthread -o block
non_block: non_blocking_mutex2019239.c
	gcc  non_blocking_mutex2019239.c -lpthread -o non_block

clean:
	rm -f block
	rm -f non_blockS