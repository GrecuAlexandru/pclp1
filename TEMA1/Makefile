# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -std=c99
 
# Regula de compilare
all: problema1 problema2 problema3 problema4

problema1: cutii.c
	$(CC) -o problema1 cutii.c $(CFLAGS)

problema2: lungi.c
	$(CC) -o problema2 lungi.c $(CFLAGS)

problema3: codificari.c
	$(CC) -o problema3 codificari.c $(CFLAGS)

problema4: masini.c
	$(CC) -o problema4 masini.c $(CFLAGS)


# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f problema1 problema2 problema3 problema4
	rm -f *.out
	rm my_diff
