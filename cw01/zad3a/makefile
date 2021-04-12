CC = gcc -Wall -g
ss = testSamples/smallshortA.txt:testSamples/smallshortB.txt
sm = testSamples/smallmediumA.txt:testSamples/smallmediumB.txt
sl = testSamples/smalllongA.txt:testSamples/smalllongB.txt
ms = testSamples/mediumshortA.txt:testSamples/mediumshortB.txt
mm = testSamples/mediummediumA.txt:testSamples/mediummediumB.txt
ml = testSamples/mediumlongA.txt:testSamples/mediumlongB.txt
bs = testSamples/bigshortA.txt:testSamples/bigshortB.txt
bm = testSamples/bigmediumA.txt:testSamples/bigmediumB.txt
bl = testSamples/biglongA.txt:testSamples/biglongB.txt

main_dynamic: shared main_dynamic.c
	$(CC) -o main main_dynamic.c -Wl,-rpath='$$ORIGIN' -ldl -I . 

main_static: static main.c
	$(CC) -c main.c
	$(CC) -g  main.o -l textmergelib -L ./ -o main

main_shared: shared main.c
	$(CC)  -o main main.c -Wl,-rpath='$$ORIGIN' -L. libtextmergelib.so -I .

shared: textmergelib.c textmergelib.h
	$(CC) -fPIC -c textmergelib.c
	$(CC) -shared -o libtextmergelib.so textmergelib.o

static: textmergelib.c textmergelib.h
	$(CC) -c -Wall -I.  textmergelib.c
	ar rcs libtextmergelib.a textmergelib.o

test_all: main_static
	make test_static
	make main_shared
	make test_shared
	make main_dynamic
	make test_dynamic

test_static: main_static
	echo "Tests performed with static library"
	make test

test_shared: main_shared
	echo "Tests performed with shared library"
	make test

test_dynamic: main_dynamic
	echo "Tests performed with main_dynamic library"
	make test

test: main
	make test_some_bl
	make test_some_write_remove

test_few_ss:
	echo "few small and short files"
	./main create_table 5 merge_files $(ss) $(ss) $(ss) $(ss) $(ss)
test_some_ss:
	echo "some small and short files"
	./main create_table 20 merge_files $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss)
test_a_lot_of_ss:
	echo "a lot of small and short files"
	./main create_table 100 merge_files $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss) $(ss)

test_few_sm:
	echo "few small and medium files"
	./main create_table 5 merge_files $(sm) $(sm) $(sm) $(sm) $(sm)
test_some_sm:
	echo "some small and medium files"
	./main create_table 20 merge_files $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm)
test_a_lot_of_sm:
	echo "a lot of small and medium files"
	./main create_table 100 merge_files $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm) $(sm)

test_few_sl:
	echo "few small and long files"
	./main create_table 5 merge_files $(sl) $(sl) $(sl) $(sl) $(sl) 
test_some_sl:
	echo "some small and long files"
	./main create_table 20 merge_files $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl)
test_a_lot_of_sl:
	echo "a lot of small and long files"
	./main create_table 100 merge_files $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl) $(sl)

test_few_ms:
	echo "few medium and short files"
	./main create_table 5 merge_files $(ms) $(ms) $(ms) $(ms) $(ms) 
test_some_ms:
	echo "some medium and short files"
	./main create_table 20 merge_files $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms)
test_a_lot_of_ms:
	echo "a lot of medium and short files"
	./main create_table 100 merge_files $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms) $(ms)

test_few_mm:
	echo "few medium and medium files"
	./main create_table 5 merge_files $(mm) $(mm) $(mm) $(mm) $(mm)
test_some_mm:
	echo "some medium and medium files"
	./main create_table 20 merge_files $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm)
test_a_lot_of_mm:
	echo "a lot of medium and medium files"
	./main create_table 100 merge_files $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm) $(mm)

test_few_ml:
	echo "few medium and long files"
	./main create_table 5 merge_files $(ml) $(ml) $(ml) $(ml) $(ml)
test_some_ml:
	echo "some medium and long files"
	./main create_table 20 merge_files $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml)
test_a_lot_of_ml:
	echo "a lot of medium and long files"
	./main create_table 100 merge_files $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml) $(ml)

test_few_bs:
	echo "few big and short files"
	./main create_table 5 merge_files $(bs) $(bs) $(bs) $(bs) $(bs) 
test_some_bs:
	echo "some big and short files"
	./main create_table 20 merge_files $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs)
test_a_lot_of_bs:
	echo "a lot of big and short files"
	./main create_table 100 merge_files $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs) $(bs)

test_few_bm:
	echo "few big and medium files"
	./main create_table 5 merge_files $(bm) $(bm) $(bm) $(bm) $(bm)  
test_some_bm:
	echo "some big and medium files"
	./main create_table 20 merge_files $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm)
test_a_lot_of_bm:
	echo "a lot of big and medium files"
	./main create_table 100 merge_files $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm) $(bm)

test_few_bl:
	echo "few big and long files"
	./main create_table 5 merge_files $(bl) $(bl) $(bl) $(bl) $(bl)
test_some_bl:
	echo "some big and long files"
	./main create_table 20 merge_files $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl)
test_a_lot_of_bl:
	echo "a lot of big and long files"
	./main create_table 100 merge_files $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl) $(bl)

test_few_write_remove:
	echo "few write remove"
	./main create_table 1 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 
test_some_write_remove:
	echo "some write remove"
	./main create_table 1 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 
test_a_lot_of_write_remove:
	echo "a lot of write remove"
	./main create_table 1 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 merge_files $(bl) remove_block 0 

clean:
	rm -f *o
	rm -f *a
	rm main
	rm -f temp.txt
