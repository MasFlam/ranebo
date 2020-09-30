CC := gcc
CCFLAGS := -ansi

.PHONY: all clean compile

all: clean compile
clean:
	rm *.o ranebo
compile: main.c


main.c: ranebo.c
	$(CC) $(CCFLAGS) main.c *.o -o ranebo

ranebo.c: ranebo.h
	$(CC) $(CCFLAGS) -c ranebo.c -o ranebo.o
