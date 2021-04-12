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

run: main
	./main 20
main: main.c
	$(CC) main.c -o main

clean:
	rm -f *o
	rm -f *a
	rm -f main_sys
	rm -f main_lib
	rm -f test.txt 