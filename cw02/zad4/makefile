CC = gcc -Wall -g
ss = testSamples/smallshortA.txt
sm = testSamples/smallmediumA.txt
sl = testSamples/smalllongA.txt
ms = testSamples/mediumshortA.txt
mm = testSamples/mediummediumA.txt
ml = testSamples/mediumlongA.txt
bs = testSamples/bigshortA.txt
bm = testSamples/bigmediumA.txt
bl = testSamples/biglongA.txt

run_lib: main_lib
	./main_lib $(bl) test.txt quis COKOLWIEK

main_lib: main_lib.c
	$(CC) main_lib.c -o main_lib

run_sys: main_sys
	./main_sys $(bl) test.txt quis COKOLWIEK
	
main_sys: main_sys.c
	$(CC) main_sys.c -o main_sys

all:
	make main_lib
	make main_sys

test:
	make run_sys
	make run_lib

clean:
	rm -f *o
	rm -f *a
	rm -f main_sys
	rm -f main_lib
	rm -f test.txt