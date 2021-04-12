CC = gcc -Wall -g

all: static shared

static: textmergelib.c textmergelib.h
	$(CC) -c -Wall -I.  textmergelib.c
	ar rcs libtextmergelib.a textmergelib.o

shared: textmergelib.c textmergelib.h
	$(CC) -fPIC -c textmergelib.c
	$(CC) -shared -o libtextmergelib.so textmergelib.o

clean:
	rm -f *o
	rm -f *a