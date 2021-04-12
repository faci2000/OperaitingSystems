CC = gcc -Wall -g
ss = testSamples/smallshortA.txt testSamples/smallshortB.txt
sm = testSamples/smallmediumA.txt testSamples/smallmediumB.txt
sl = testSamples/smalllongA.txt testSamples/smalllongB.txt
ms = testSamples/mediumshortA.txt testSamples/mediumshortB.txt
mm = testSamples/mediummediumA.txt testSamples/mediummediumB.txt
ml = testSamples/mediumlongA.txt testSamples/mediumlongB.txt
bs = testSamples/bigshortA.txt testSamples/bigshortB.txt
bm = testSamples/bigmediumA.txt testSamples/bigmediumB.txt
bl = testSamples/biglongA.txt testSamples/biglongB.txt

run_sys: main_sys
	./main_sys $(bs)

run_lib: main_lib
	./main_lib $(bs)

main_lib: main_lib.c
	$(CC) main_lib.c -o main_lib


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
