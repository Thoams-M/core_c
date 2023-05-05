all:
	gcc coeur.c -w -o core
	./core
	rm core
	rm sauvegarde.bin
