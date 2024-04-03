C = gcc -g3
CFLAGS = -g3

all: Project2

Project2: main.o scanner.o parser.o
        $(CC) $(CFLAGS) -o Project2 main.o scanner.o parser.o

main.o: main.c token.h scanner.h parser.h
        $(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c token.h scanner.h
        $(CC) $(CFLAGS) -c scanner.c

parser.o: parser.c token.h parser.h
        $(CC) $(CFLAGS) -c parser.c

clean:
        rm -f Project2 *.o
        rm -f filteredFile.txt
        rm -f tempfile.txt
