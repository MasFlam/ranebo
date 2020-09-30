CC := gcc
CCFLAGS := -ansi -Wall

.PHONY: all clean compile

all: clean compile
clean:
	rm -f *.o ranebo
compile: ranebo

ranebo: main.o ranebo.o
	$(CC) $(CCFLAGS) *.o -o ranebo

main.o: main.c ranebo.h
	$(CC) $(CCFLAGS) -c main.c -o main.o

ranebo.o: ranebo.c ranebo.h
	$(CC) $(CCFLAGS) -c ranebo.c -o ranebo.o
