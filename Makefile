all: lexer
CC = gcc
CCFLAGS = -c -DDEBUG -lm

lexer.o: lexer.c
	$(CC) $(CCFLAGS) lexer.c -o lexer.o

interpretator.o: interpretator.c
	$(CC) $(CCFLAGS) interpretator.c -o interpretator.o

generator.o: generator.c
	$(CC) $(CCFLAGS) generator.c -o generator.o

lexer: interpretator.o lexer.o generator.o
	$(CC) interpretator.o lexer.o generator.o -o lexer

clean:; rm -rf *.o lexer program.bin