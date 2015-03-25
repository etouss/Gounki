SOURCES=grille.c heuristique.c Jouer.c main.c partieHeuristique.c persistance.c pion.c test.c modeTest.c
OBJECTS=$(SOURCES:.c=.o)
CFLAGS= -Wall -pthread -g
EXECUTABLE=gounki


$(EXECUTABLE): $(OBJECTS)
	gcc -o $(EXECUTABLE) $(OBJECTS)

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) *.o
