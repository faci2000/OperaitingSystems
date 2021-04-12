CC = gcc -Wall -g

all: sender catcher

run_sender: sender
	./sender
run_catcher: catcher 
	./catcher 
sender: sender.c
	$(CC) sender.c -o sender

catcher: catcher.c
	$(CC) catcher.c -o catcher

n=10000
test: all	
	@echo "\n          [KILL]"
	@./catcher &
	@./sender `pidof catcher` $n KILL
	@echo "\n          [SIGQUEUE]"
	@./catcher &
	@./sender `pidof catcher` $n SIGQUEUE
	@echo "\n          [SIGRT]"
	@./catcher &
	@./sender `pidof catcher` $n SIGRT

clean:
	rm -f *o
	rm -f *a
	rm -f main
	rm -f main_exec