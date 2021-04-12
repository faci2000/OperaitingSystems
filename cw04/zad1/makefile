CC = gcc -Wall -g

test: main
	./main ignore
	./main handler
	./main mask
	./main pending
run: main
	./main handler
main: main.c
	$(CC) main.c -o main

test_exec: main_exec
	./main_exec ignore
	./main_exec mask
	./main_exec pending
	./main_exec handler
run_exec: main_exec
	./main_exec handler
main_exec: main_exec.c
	$(CC) main_exec.c -o main_exec

clean:
	rm -f *o
	rm -f *a
	rm -f main
	rm -f main_exec