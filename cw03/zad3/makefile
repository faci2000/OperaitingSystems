CC = gcc -Wall -g

test: main
	./main testSamples Pan 1
	./main testSamples Pan 2
	./main testSamples Pan 3
	./main testSamples Pan 4
	./main testSamples Pan 5S

run: main
	./main testSamples Pan 4
main: main.c
	$(CC) main.c -o main

clean:
	rm -f *o
	rm -f *a
	rm -f main
	rm -f *txt 