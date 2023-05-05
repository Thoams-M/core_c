all:
	gcc coeur.c -w -o core
	./core
clean:
	rm core
